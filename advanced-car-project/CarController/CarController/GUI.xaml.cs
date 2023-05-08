using System.Collections.ObjectModel;
using System.IO;
using System.Net;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace CarController
{
    public partial class MainWindow : Window
    {
        ObservableCollection<Command> lb_command_entries;
        bool action_key_pressed = false;

        public MainWindow()
        {
            InitializeComponent();

            /* Initialize resources for the ListBox */
            lb_command_entries = new ObservableCollection<Command>();
            DataContext = lb_command_entries;

            /* Initialize Label */
            hotkey_label.Content = 
                            " H o t k e y s:\n" +
                            "=============================\n" +
                            " 1     -   Headlight\n" +
                            " 2     -   LCD backlight\n" +
                            " 3     -   LCD info mode\n" +
                            " 4     -   Turn mode\n" +
                            " 5     -   FCA mode\n\n" +
                            " Up    -   Moving forward\n" +
                            " Down  -   Moving backward\n" +
                            " Right -   Moving right\n" +
                            " Left  -   Moving left\n" +
                            " 0     -   Moving stop\n";
        }

        private void UserControl_Loaded(object sender, RoutedEventArgs e)
        {
            var window = Window.GetWindow(this);
            window.KeyDown += HandleKeyPress;
            window.KeyUp += HandleKeyRelease;
        }

        private async void HandleHttpGetRequests(Command cmd)
        {
            // Update Listbox view with the request - Insert the command details to the top row of the listbox.
            lb_command_entries.Insert(0, cmd);

            try
            {
                // Update Listbox view with the response
                lb_command_entries.Insert(0, new Command(await GetAsync(Configuration.SERVER + cmd.Id)));
            }
            catch (WebException ex)
            {
                // Handle exeption if there is no response from the car
                lb_command_entries.Insert(0, new Command(Configuration.ERROR__http_timeout));
            }
            
        }

        private void HandleKeyRelease(object sender, KeyEventArgs e)
        {
            action_key_pressed = false;
            if ((e.Key == Key.Up) || (e.Key == Key.Down) || (e.Key == Key.Right) || (e.Key == Key.Left))
                HandleHttpGetRequests(new Command(Configuration.COMMAND__stop));
        }

        private void HandleKeyPress(object sender, KeyEventArgs e)
        {
            if (action_key_pressed == false)
            {
                action_key_pressed = true;
                switch (e.Key)
                {
                    case Key.D1:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__headlight));
                        break;
                    case Key.D2:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__lcd_backlight));
                        break;
                    case Key.D3:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__lcd_info));
                        break;
                    case Key.D4:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__turn_mode));
                        break;
                    case Key.D5:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__fca));
                        break;
                    case Key.D0:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__stop));
                        break;
                    case Key.Up:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__forward));
                        break;
                    case Key.Down:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__backward));
                        break;
                    case Key.Right:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__right));
                        break;
                    case Key.Left:
                        HandleHttpGetRequests(new Command(Configuration.COMMAND__left));
                        break;
                    default:
                        /* do nothing */
                        break;
                }
            }
        }

        public async Task<string> GetAsync(string uri)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(uri);

            // The reason behind the slow web requests is the proxy property. 
            // If proxy property set to null before calling the GetResponse method the query will skip the proxy autodetect step which could take a while...
            request.Proxy = null;

            using (HttpWebResponse response = (HttpWebResponse)await request.GetResponseAsync())
            using (Stream stream = response.GetResponseStream())
            using (StreamReader reader = new StreamReader(stream))
            {
                return await reader.ReadToEndAsync();
            }
        }

    }
}
