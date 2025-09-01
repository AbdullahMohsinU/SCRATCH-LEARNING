// No includes

// Declare Windows functions
extern "C" {
    void* __stdcall GetModuleHandleA(const char*);
    void* __stdcall LoadCursorA(void*, const char*);
    void* __stdcall LoadIconA(void*, const char*);
    void* __stdcall CreateWindowExA(unsigned long, const char*, const char*, unsigned long, int, int, int, int, void*, void*, void*, void*);
    int   __stdcall ShowWindow(void*, int);
    int   __stdcall UpdateWindow(void*);
    int   __stdcall GetMessageA(void*, void*, unsigned int, unsigned int);
    int   __stdcall TranslateMessage(void*);
    int   __stdcall DispatchMessageA(void*);
    int   __stdcall DefWindowProcA(void*, unsigned int, unsigned long, long);
    void* __stdcall RegisterClassA(const void*);
    void* __stdcall GetDC(void*);
    unsigned int __stdcall SetTextColor(void*, unsigned int);
    unsigned int __stdcall SetBkColor(void*, unsigned int);
    int __stdcall TextOutA(void*, int, int, const char*, int);
    int __stdcall ReleaseDC(void*, void*);
}

// Structures
typedef struct {
    unsigned int style;
    void*        lpfnWndProc;
    int          cbClsExtra;
    int          cbWndExtra;
    void*        hInstance;
    void*        hIcon;
    void*        hCursor;
    void*        hbrBackground;
    const char*  lpszMenuName;
    const char*  lpszClassName;
} WNDCLASSA;

typedef struct {
    void* hwnd;
    unsigned int message;
    unsigned long wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
} MSG;

// Constants
#define WS_OVERLAPPEDWINDOW 0x00CF0000
#define WS_VISIBLE 0x10000000
#define CW_USEDEFAULT 0x80000000
#define IDC_ARROW ((const char*)32512)
#define IDI_APPLICATION ((const char*)32512)
#define COLOR_BLUE 1
#define SW_SHOW 5
#define WM_DESTROY 0x0002
#define WM_PAINT   0x000F
#define WM_CLOSE   0x0010

// Window Procedure
extern "C" int __stdcall WndProc(void* hwnd, unsigned int msg, unsigned long wp, long lp) {
    if (msg == WM_PAINT) {
        void* hdc = GetDC(hwnd);

        // Set colors
        SetBkColor(hdc, 0x000000FF);      // Blue background (in BGR format)
        SetTextColor(hdc, 0x00FFFFFF);    // White text

        const char* text = "Welcome to COOK Window!";
        int len = 0;
        while (text[len]) ++len;

        // Draw text
        TextOutA(hdc, 100, 100, text, len);
        ReleaseDC(hwnd, hdc);
    }

    if (msg == WM_CLOSE || msg == WM_DESTROY) {
        *((int*)0) = 0; // crash to exit (or use ExitProcess if allowed)
    }

    return DefWindowProcA(hwnd, msg, wp, lp);
}

int main() {
    void* hInst = GetModuleHandleA(0);

    WNDCLASSA wc = {};
    wc.lpfnWndProc = (void*)WndProc;
    wc.hInstance = hInst;
    wc.hIcon = LoadIconA(0, IDI_APPLICATION);
    wc.hCursor = LoadCursorA(0, IDC_ARROW);
    wc.hbrBackground = (void*)(COLOR_BLUE + 1);  // Blue background
    wc.lpszClassName = "CookWin";

    RegisterClassA(&wc);

    void* hwnd = CreateWindowExA(
        0, "CookWin", "COOK GRAPHICS",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        200, 200, 600, 400,
        0, 0, hInst, 0
    );

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageA(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}

