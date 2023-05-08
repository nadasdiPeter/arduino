using System;

namespace CarController
{
    class Command
    {
        private string id;
        private string name;
        private category_t category;
        private direction_t direction;
        private device_t sender;
        private device_t receiver;
        private string time;
        private string color;

        public Command(string id)
        {
            switch (id)
            {
                case Configuration.COMMAND__stop:
                    this.Name = "stop";
                    this.Category = category_t.MOVE;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__forward:
                    this.Name = "forward";
                    this.Category = category_t.MOVE;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__backward:
                    this.Name = "backward";
                    this.Category = category_t.MOVE;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__left:
                    this.Name = "left";
                    this.Category = category_t.MOVE;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__right:
                    this.Name = "right";
                    this.Category = category_t.MOVE;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__headlight:
                    this.Name = "headlight";
                    this.Category = category_t.ACTION;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__lcd_backlight:
                    this.Name = "lcd-backlight";
                    this.Category = category_t.ACTION;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__lcd_info:
                    this.Name = "information-mode";
                    this.Category = category_t.ACTION;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__turn_mode:
                    this.Name = "turn-mode";
                    this.Category = category_t.ACTION;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__fca:
                    this.Name = "fca-mode";
                    this.Category = category_t.ACTION;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.ERROR__http_timeout:
                    this.Name = "HTTPWebException::Timeout";
                    this.Category = category_t.ERROR;
                    this.Id = id;
                    this.Direction = direction_t.tx;
                    this.Sender = device_t.controller;
                    this.Receiver = device_t.car;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__moveB_accepted:
                case Configuration.COMMAND__moveF_accepted:
                case Configuration.COMMAND__moveL_accepted:
                case Configuration.COMMAND__moveR_accepted:
                case Configuration.COMMAND__moveS_accepted:
                    this.Name = "accepted";
                    this.Category = category_t.MOVE;
                    this.Id = id;
                    this.Direction = direction_t.rx;
                    this.Sender = device_t.car;
                    this.Receiver = device_t.controller;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__action_fcamode_accepted:
                case Configuration.COMMAND__action_headlight_accapted:
                case Configuration.COMMAND__action_infomode_accepted:
                case Configuration.COMMAND__action_lcd_accepted:
                case Configuration.COMMAND__action_turnmode_accepted:
                    this.Name = "accepted";
                    this.Category = category_t.ACTION;
                    this.Id = id;
                    this.Direction = direction_t.rx;
                    this.Sender = device_t.car;
                    this.Receiver = device_t.controller;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                case Configuration.COMMAND__action_declined:
                case Configuration.COMMAND__moveU_declined:
                    this.Name = "declined";
                    this.Category = category_t.ERROR;
                    this.Id = id;
                    this.Direction = direction_t.rx;
                    this.Sender = device_t.car;
                    this.Receiver = device_t.controller;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
                default:
                    this.Name = "unknown";
                    this.Category = category_t.NA;
                    this.Id = id;
                    this.Direction = direction_t.rx;
                    this.Sender = device_t.car;
                    this.Receiver = device_t.controller;
                    this.Time = DateTime.Now.ToString("[HH:mm:ss]");
                    break;
            }

            if (this.Direction == direction_t.rx)
                this.Color = "Blue";
            else
                this.Color = "Black";

            if (this.category == category_t.ERROR)
                this.Color = "Red";

        }

        public string Id { get => id; set => id = value; }
        public string Name { get => name; set => name = value; }
        public category_t Category { get => category; set => category = value; }
        public string Time { get => time; set => time = value; }
        public string Color { get => color; set => color = value; }
        internal direction_t Direction { get => direction; set => direction = value; }
        internal device_t Sender { get => sender; set => sender = value; }
        internal device_t Receiver { get => receiver; set => receiver = value; }
    }
}
