namespace CarController
{
    enum direction_t { rx, tx };

    enum device_t { car, controller };

    enum command_t { request, response };

    class Configuration
    {
        public const string IP = "192.168.4.1";
        public const string PORT = "8080";
        public const string SERVER = @"http://" + IP + ":" + PORT + "/";

        public const string COMMAND__stop = "move?dir=S";
        public const string COMMAND__forward = "move?dir=F";
        public const string COMMAND__backward = "move?dir=B";
        public const string COMMAND__left = "move?dir=L";
        public const string COMMAND__right = "move?dir=R";
        public const string COMMAND__headlight = "action?type=1";
        public const string COMMAND__lcd_backlight = "action?type=2";
        public const string COMMAND__lcd_info = "action?type=3";
        public const string COMMAND__turn_mode = "action?type=4";
        public const string COMMAND__fca = "action?type=5";
    }
}
