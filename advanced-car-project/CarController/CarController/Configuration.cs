namespace CarController
{
    enum direction_t { rx, tx };

    enum device_t { car, controller };

    enum command_t { request, response };

    enum category_t { MOVE, ACTION, NA, ERROR };

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

        public const string COMMAND__moveU_declined = "Move/undefined::DECLINED";
        public const string COMMAND__moveF_accepted = "Move/forward::ACCEPTED";
        public const string COMMAND__moveB_accepted = "Move/backward::ACCEPTED";
        public const string COMMAND__moveS_accepted = "Move/stop::ACCEPTED";
        public const string COMMAND__moveL_accepted = "Move/left::ACCEPTED";
        public const string COMMAND__moveR_accepted = "Move/right::ACCEPTED";
        public const string COMMAND__action_declined = "Action/undefined::DECLINED";
        public const string COMMAND__action_headlight_accapted = "Action/hedlight::ACCEPTED";
        public const string COMMAND__action_lcd_accepted = "Action/lcd::ACCEPTED";
        public const string COMMAND__action_infomode_accepted = "Action/info-mode::ACCEPTED";
        public const string COMMAND__action_turnmode_accepted = "Action/turn-mode::ACCEPTED";
        public const string COMMAND__action_fcamode_accepted = "Action/fca-mode::ACCEPTED";

        public const string ERROR__http_timeout = "WebException-Timeout";

    }
}
