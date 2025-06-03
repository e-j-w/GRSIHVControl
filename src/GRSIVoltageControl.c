// Logs into HV crate

#include "CAENHVWrapper.h"
#include "GRSIVoltageControl.h"
#include "CrateCommands.h"
#include "CommandParser.h"

HV System[MAX_HVPS];

//#==============================================================================
//# MAIN
//#==============================================================================

int main(int argc, char *argv[])
{

   if(argc < 4){
      printf("ERROR: not enough arguments.  Need:\n");
      printf("./GRSIHVControl <arguments> <host> <user> <passwd>\n");
      return 0;
   }

   char userName[20];
   char passwd[20];
   char hvSysName[80];
   int ret;

   // copies credentials to strings so they're modifiable (modifying argv = bad)
   strncpy(hvSysName, argv[argc - 3],80);
   strncpy(userName, argv[argc - 2],20);
   strncpy(passwd, argv[argc - 1],20);

   for( ret = 0; ret < MAX_HVPS; ret++ ){
      System[ret].ID = -1;
   }

   // login to HVCrate
   HVSystemLogin(hvSysName, (const char *)userName, (const char *)passwd);

   ParseInputs(argc, argv);

   // logout of crate
   HVSystemLogout();

   return 0;
}
