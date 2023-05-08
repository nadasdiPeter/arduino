namespace CarController
{
    class Command
    {
        private string id;
        private string name;
        private string category;
        private direction_t direction;
        private device_t sender;
        private device_t receiver;

        public Command(string id)
        {
            switch (id)
            {
                case Configuration.COMMAND__stop:
                    this.Name = "stop";
                    this.Category = "move";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                case Configuration.COMMAND__forward:
                    this.Name = "forward";
                    this.Category = "move";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                case Configuration.COMMAND__backward:
                    this.Name = "backward";
                    this.Category = "move";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                case Configuration.COMMAND__left:
                    this.Name = "left";
                    this.Category = "move";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                case Configuration.COMMAND__right:
                    this.Name = "right";
                    this.Category = "move";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                case Configuration.COMMAND__headlight:
                    this.Name = "headlight";
                    this.Category = "action";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                case Configuration.COMMAND__lcd_backlight:
                    this.Name = "lcd-backlight";
                    this.Category = "action";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                case Configuration.COMMAND__lcd_info:
                    this.Name = "information-mode";
                    this.Category = "action";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                case Configuration.COMMAND__turn_mode:
                    this.Name = "turn-mode";
                    this.Category = "action";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                case Configuration.COMMAND__fca:
                    this.Name = "fca-mode";
                    this.Category = "action";
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    break;
                default:
                    this.Name = "unknown";
                    this.Category = "n.a.";
                    this.Id = id;
                    this.Direction = direction_t.rx;
                    this.Sender = device_t.car;
                    this.Receiver = device_t.controller;
                    break;
            }
        }

        public string Id { get => id; set => id = value; }
        public string Name { get => name; set => name = value; }
        public string Category { get => category; set => category = value; }
        internal direction_t Direction { get => direction; set => direction = value; }
        internal device_t Sender { get => sender; set => sender = value; }
        internal device_t Receiver { get => receiver; set => receiver = value; }
    }
}
