extern void display_main(connection_status_t connection);
extern void Set_display_info_mode(display_info_mode_t mode);
extern void Next_display_info_mode();
extern void initialize_lcd_display();
extern void toggle_lcd_backlight();
extern void write_unconnected_display_message();
extern void update_1st_line_command(connection_status_t connection);
extern void update_lcd_display_text(connection_status_t connection, int command_id = 0);
extern serial_command_t update_2nd_line_command(serial_command_t command, msg_direction_t msg_dir = rx);