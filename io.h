size_t get_homedir_path(char* result);
size_t get_ticketsdir_path(char* result);
int create_tickets_dir();
int get_next_ticketnum();
FILE* get_ticket_file(int num);
int write_new_ticket();
