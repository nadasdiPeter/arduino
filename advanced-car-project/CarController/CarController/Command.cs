using System;
using System.Text.RegularExpressions;

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
      private string tooltip;

      public Command(string id)
      {
         string move_pattern = @".*[mM]ove{1}.*";
         string action_pattern = @".*[aA]ction{1}.*";

         this.Name = GetNameFromID(id);
         this.Category = (Regex.IsMatch(id, move_pattern)) ? category_t.MOVE : (Regex.IsMatch(id, action_pattern)) ? category_t.ACTION : category_t.ERROR;
         this.Time = DateTime.Now.ToString("[HH:mm:ss]");
         this.Id = id;

         switch (id)
         {
            case Configuration.COMMAND__stop:
            case Configuration.COMMAND__forward:
            case Configuration.COMMAND__backward:
            case Configuration.COMMAND__left:
            case Configuration.COMMAND__right:
            case Configuration.COMMAND__headlight:
            case Configuration.COMMAND__lcd_backlight:
            case Configuration.COMMAND__lcd_info:
            case Configuration.COMMAND__turn_mode:
            case Configuration.COMMAND__fca:
            case Configuration.ERROR__http_timeout:
               this.Direction = direction_t.tx;
               this.Sender = device_t.controller;
               this.Receiver = device_t.car;
               break;
            case Configuration.COMMAND__moveB_accepted:
            case Configuration.COMMAND__moveF_accepted:
            case Configuration.COMMAND__moveL_accepted:
            case Configuration.COMMAND__moveR_accepted:
            case Configuration.COMMAND__moveS_accepted:
            case Configuration.COMMAND__action_fcamode_accepted:
            case Configuration.COMMAND__action_headlight_accapted:
            case Configuration.COMMAND__action_infomode_accepted:
            case Configuration.COMMAND__action_lcd_accepted:
            case Configuration.COMMAND__action_turnmode_accepted:
            case Configuration.COMMAND__action_declined:
            case Configuration.COMMAND__moveU_declined:
               this.Direction = direction_t.rx;
               this.Sender = device_t.car;
               this.Receiver = device_t.controller;
               break;
            default:
               this.Direction = direction_t.rx;
               this.Sender = device_t.car;
               this.Receiver = device_t.controller;
               break;
         }

         // Taking care about the coloring in listBox
         if (this.Direction == direction_t.rx)
            this.Color = "Blue";
         else
            this.Color = "Black";

         if (this.category == category_t.ERROR)
            this.Color = "Red";

         // Taking care about the tooltip text in listBox
         this.Tooltip = this.Sender + " >> " + this.Receiver + " :: " + this.Id;

      }

      private string GetNameFromID(string id)
      {
         switch (id)
         {
            case Configuration.COMMAND__stop:
               return "stop";
            case Configuration.COMMAND__forward:
               return "forward";
            case Configuration.COMMAND__backward:
               return "backward";
            case Configuration.COMMAND__left:
               return "left";
            case Configuration.COMMAND__right:
               return "right";
            case Configuration.COMMAND__headlight:
               return "headlight";
            case Configuration.COMMAND__lcd_backlight:
               return "lcd-backlight";
            case Configuration.COMMAND__lcd_info:
               return "information-mode";
            case Configuration.COMMAND__turn_mode:
               return "turn-mode";
            case Configuration.COMMAND__fca:
               return "fca-mode";
            case Configuration.ERROR__http_timeout:
               return "HTTPWebException::Timeout";
            case Configuration.COMMAND__moveB_accepted:
               return "move:backward > accepted";
            case Configuration.COMMAND__moveF_accepted:
               return "move:forward > accepted";
            case Configuration.COMMAND__moveL_accepted:
               return "move:left > accepted";
            case Configuration.COMMAND__moveR_accepted:
               return "move:right> accepted";
            case Configuration.COMMAND__moveS_accepted:
               return "move:stop > accepted";
            case Configuration.COMMAND__action_fcamode_accepted:
               return "action:fca > accepted";
            case Configuration.COMMAND__action_headlight_accapted:
               return "action:headlight > accepted";
            case Configuration.COMMAND__action_infomode_accepted:
               return "action:infomode > accepted";
            case Configuration.COMMAND__action_lcd_accepted:
               return "action:lcd > accepted";
            case Configuration.COMMAND__action_turnmode_accepted:
               return "action:turnmode > accepted";
            case Configuration.COMMAND__action_declined:
               return "action:unknown > declined";
            case Configuration.COMMAND__moveU_declined:
               return "action:undefined > declined";
            default:
               return "cmd:undefined > declined";
         }
      }
      public string Id { get => id; set => id = value; }
      public string Name { get => name; set => name = value; }
      public category_t Category { get => category; set => category = value; }
      public string Time { get => time; set => time = value; }
      public string Color { get => color; set => color = value; }
      internal direction_t Direction { get => direction; set => direction = value; }
      internal device_t Sender { get => sender; set => sender = value; }
      internal device_t Receiver { get => receiver; set => receiver = value; }
      public string Tooltip { get => tooltip; set => tooltip = value; }
   }
}
