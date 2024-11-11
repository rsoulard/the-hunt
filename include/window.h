typedef struct Window* window_t;

window_t Window_New();
void Window_Destroy(window_t this);
void Window_OnStart(window_t this);
void Window_Process(window_t this);
void Window_OnEnd(window_t this);