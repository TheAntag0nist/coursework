#ifdef _WIN32
    void SetColor(int ForgC);
#endif
void inf_message(char* message,char flag_sym, char* add_str);
void fatal(char* message);
void* errch_malloc(unsigned int mem_size);
int arg_prog(char* message);
char* get_time();