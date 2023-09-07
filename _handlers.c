#include "main.h"

void _ctrl_c_handler(__attribute__((unused)) int signal)
{
	if (isatty(STDIN_FILENO) == 1)
		dprintf(STDOUT_FILENO, "\n($) ");
}
