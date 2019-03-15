#include <stdio.h>
#include "readline/readline.h"
#include "kemmens/logger.h"
#include "kemmens/CommandInterpreter.h"
#include "kemmens/megekemmen.h"
#include "kemmens/StringUtils.h"

void Command_Echo(int argC, char** args, char* callingLine, void* extraData)
{

	char* echoString = string_new();

	for(int i = 1; i <= argC;i++)
	{
		string_append(&echoString, args[i]);
		string_append(&echoString, " ");
	}

	printf("%s\n", echoString);

	free(echoString);

	CommandInterpreter_FreeArguments(args);
}

void Command_Double(int argC, char** args, char* callingLine, void* extraData)
{

	if(argC < 1)
	{
		printf("Uso: double <numero>\n");
	} else {

		int val = atoi(args[1]);

		printf("%d\n", (val*2));
	}
	CommandInterpreter_FreeArguments(args);
}

int main()
{
	Logger_CreateLog("./chatapp.log", "CHARAPP", true);
	Logger_Log(LOG_INFO, "Iniciando App...");
	CommandInterpreter_Init(); //Inicializar el Command Interpreter
	CommandInterpreter_RegisterCommand("echo", Command_Echo);
	CommandInterpreter_RegisterCommand("double", Command_Double);

	while(1)
	{
		char* line = readline("> ");
		if(line == NULL)
			continue;

		if(strcmp("exit", line) == 0)
			break;

		if(!CommandInterpreter_Do(line, " ", NULL)) //Si devuelve false entonces no encontro ningun comando
		{
			printf("Comando no valido!\n");
		}

		free(line);
	}

	exit_gracefully(0); //Libera memoria del logger y del command interpreter!
}

