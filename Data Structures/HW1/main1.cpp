/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2010                                          */
/*                                                                         */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/



#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "library1.h"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif




/* The command's strings */
typedef enum {
  NONE_CMD = -2,
  COMMENT_CMD = -1,
  INIT_CMD = 0,
  ADDCANDIDATE_CMD = 1,
  HIRECANDIDATE_CMD = 2,
  HIRECHEAPESTCANDIDATE_CMD = 3,
  HIREFIRSTCANDIDATE_CMD = 4,
  INCREASEAVERAGEMARKETSALARY_CMD = 5,
  GETREQUESTEDSALARY_CMD = 6,
  AVERAGEREQUESTEDSALARY_CMD = 7,
  MEDIANREQUESTEDSALARY_CMD = 8,
  MINIMALFIELDSALARY_CMD = 9,
  AVERAGEOFFIRSTKINFIELD_CMD = 10,
  QUIT_CMD = 11
} commandType;



static const int   numActions   = 12;
static const char *commandStr[] = {
  "Init",
  "AddCandidate",
  "HireCandidate",
  "HireCheapestCandidate",
  "HireFirstCandidate",
  "IncreaseAverageMarketSalary",
  "GetRequestedSalary",
  "AverageRequestedSalary",
  "MedianRequestedSalary",
  "MinimalFieldSalary",
  "AverageOfFirstKInField",
  "Quit"
};


static const char* ReturnValToStr(int val) {
	switch (val) {
		case (SUCCESS):          return "Success";
		case (FAILURE):          return "Failure";
		case (ALLOCATION_ERROR): return "Allocation_error";
		case (INVALID_INPUT):    return "Invalid_input";
		default:                 return "";
	}
}
	





/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {error_free, error} errorType;
static errorType parser(const char* const command);



#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }


static bool isInit = false;


/* Print an array */
string PrintIntArray(const int* arr, int size) {
	char buffer[MAX_BUFFER_SIZE];
	string str = "";

	for (int i=0; i < size; i++) {
		sprintf(buffer,"%d",arr[i]);
		str += string(buffer) + ((i == (size - 1)) ? "" : ",");
	}
	return str.c_str();
}




/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
  FILE* inputFile = NULL;
  if(argc == 2){
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL){
	  printf("Problem opening file %s, make sure the correct path name is given.", argv[1]);
	  return 0;
    }
  } else {
	  inputFile = stdin;
  }
  char buffer[MAX_STRING_INPUT_SIZE];
  // Reading commands
  while ( fgets(buffer, MAX_STRING_INPUT_SIZE, inputFile) != NULL ) {
    fflush(stdout); 
    if ( parser(buffer) == error )
      break;
  };
  fclose(inputFile);
  return 0;
};

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command, const char** const command_arg) {
  if ( command == NULL || strlen(command) == 0 || StrCmp("\n", command) )
    return(NONE_CMD);
  if ( StrCmp("#", command) ) {
    if (strlen(command) > 1)
      printf("%s", command);
    return(COMMENT_CMD);
  };
  for (int index=0; index < numActions; index++) {
    if ( StrCmp(commandStr[index], command) ) {
      *command_arg = command + strlen(commandStr[index]) + 1;
      return((commandType)index);
    };
  };
  return(NONE_CMD);
};

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddCandidate(void* DS, const char* const command);
static errorType OnHireCandidate(void* DS, const char* const command);
static errorType OnHireCheapestCandidate(void* DS, const char* const command);
static errorType OnHireFirstCandidate(void* DS, const char* const command);
static errorType OnIncreaseAverageMarketSalary(void* DS, const char* const command);
static errorType OnGetRequestedSalary(void* DS, const char* const command);
static errorType OnAverageRequestedSalary(void* DS, const char* const command);
static errorType OnMedianRequestedSalary(void* DS, const char* const command);
static errorType OnMinimalFieldSalary(void* DS, const char* const command);
static errorType OnAverageOfFirstKInField(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);




/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) { 
  static void *DS = NULL; /* The general data structure */
  const char* command_args = NULL;
  errorType rtn_val = error;

  commandType command_val = CheckCommand(command, &command_args);
 
  switch (command_val) {

	case (INIT_CMD):						rtn_val = OnInit(&DS, command_args);						break;
	case (ADDCANDIDATE_CMD):				rtn_val = OnAddCandidate(DS, command_args);					break;
	case (HIRECANDIDATE_CMD):				rtn_val = OnHireCandidate(DS, command_args);				break;
	case (HIRECHEAPESTCANDIDATE_CMD):		rtn_val = OnHireCheapestCandidate(DS, command_args);		break;
	case (HIREFIRSTCANDIDATE_CMD):			rtn_val = OnHireFirstCandidate(DS, command_args);			break;
	case (INCREASEAVERAGEMARKETSALARY_CMD):	rtn_val = OnIncreaseAverageMarketSalary(DS, command_args);	break;
	case (GETREQUESTEDSALARY_CMD):			rtn_val = OnGetRequestedSalary(DS, command_args);			break;
	case (AVERAGEREQUESTEDSALARY_CMD):		rtn_val = OnAverageRequestedSalary(DS, command_args);		break;
	case (MEDIANREQUESTEDSALARY_CMD):		rtn_val = OnMedianRequestedSalary(DS, command_args);		break;
	case (MINIMALFIELDSALARY_CMD):			rtn_val = OnMinimalFieldSalary(DS, command_args);			break;
	case (AVERAGEOFFIRSTKINFIELD_CMD):		rtn_val = OnAverageOfFirstKInField(DS, command_args);		break;
	case (QUIT_CMD):						rtn_val = OnQuit(&DS, command_args);						break;
	
	case (COMMENT_CMD):						rtn_val = error_free;										break;
	case (NONE_CMD):						rtn_val = error;											break;
	default: assert(false);
  };
  return(rtn_val);
};





/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if(isInit) {
		printf("Init was already called.\n");
		return(error_free);
	};
	isInit = true;

	int	numFields;	
	ValidateRead( sscanf(command, "%d" ,&numFields), 1, "Init failed.\n" );
		
	*DS = Init(numFields);
	if( *DS == NULL ) {
		printf("Init failed.\n");
		return(error);
	};
	printf("Init done.\n");

	return error_free;
}


/***************************************************************************/
/* OnAddCandidate                                                          */
/***************************************************************************/
static errorType OnAddCandidate(void* DS, const char* const command) {
	int candID;
	int field;
	int salary;
	ValidateRead( sscanf(command, "%d %d %d",&candID,&field,&salary), 3, "AddCandidate failed.\n" );
	StatusType res = AddCandidate(DS,candID,field,salary);

	printf("AddCandidate: %s\n",ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnHireCandidate                                                         */
/***************************************************************************/
static errorType OnHireCandidate(void* DS, const char* const command) {
	int candID;
	ValidateRead( sscanf(command, "%d",&candID), 1, "HireCandidate failed.\n" );
	StatusType res = HireCandidate(DS,candID);

	printf("HireCandidate: %s\n", ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnHireCheapestCandidate                                                 */
/***************************************************************************/
static errorType OnHireCheapestCandidate(void* DS, const char* const command) {
	int field;
	ValidateRead( sscanf(command, "%d",&field), 1, "HireCheapestCandidate failed.\n" );
	StatusType res = HireCheapestCandidate(DS,field);

	printf("HireCheapestCandidate: %s\n", ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnHireFirstCandidate                                                    */
/***************************************************************************/
static errorType OnHireFirstCandidate(void* DS, const char* const command) {
	int field;
	ValidateRead( sscanf(command, "%d",&field), 1, "HireFirstCandidate failed.\n" );
	StatusType res = HireFirstCandidate(DS,field);
	
	printf("HireFirstCandidate: %s\n",ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnIncreaseAverageMarketSalary                                           */
/***************************************************************************/
static errorType OnIncreaseAverageMarketSalary(void* DS, const char* const command) {
	int update;
	ValidateRead( sscanf(command, "%d",&update), 1, "IncreaseAverageMarketSalary failed.\n" );
	StatusType res = IncreaseAverageMarketSalary(DS,update);
	
	printf("IncreaseAverageMarketSalary: %s\n",ReturnValToStr(res));

	return error_free;
}


/***************************************************************************/
/* OnGetRequestedSalary                                                    */
/***************************************************************************/
static errorType OnGetRequestedSalary(void* DS, const char* const command) {
	int candID;
	ValidateRead( sscanf(command, "%d",&candID), 1, "GetRequestedSalary failed.\n" );
	int	salary;
	StatusType res = GetRequestedSalary(DS,candID,&salary);
	
	if (res != SUCCESS) {
		printf("GetRequestedSalary: %s\n",ReturnValToStr(res));
	}
	else {
		printf("GetRequestedSalary: %s %d\n", ReturnValToStr(res),salary);
	}

	return error_free;
}


/***************************************************************************/
/* OnAverageRequestedSalary                                                */
/***************************************************************************/
static errorType OnAverageRequestedSalary(void* DS, const char* const command) {
	double	average;
	StatusType res = AverageRequestedSalary(DS,&average);
	
	if (res != SUCCESS) {
		printf("AverageRequestedSalary: %s\n",ReturnValToStr(res));
	}
	else {
		printf("AverageRequestedSalary: %s %f\n", ReturnValToStr(res),average);
	}

	return error_free;
}


/***************************************************************************/
/* OnMedianRequestedSalary                                                 */
/***************************************************************************/
static errorType OnMedianRequestedSalary(void* DS, const char* const command) {
	int	median;
	StatusType res = MedianRequestedSalary(DS,&median);
	
	if (res != SUCCESS) {
		printf("MedianRequestedSalary: %s\n",ReturnValToStr(res));
	}
	else {
		printf("MedianRequestedSalary: %s %d\n", ReturnValToStr(res),median);
	}

	return error_free;
}


/***************************************************************************/
/* OnMinimalFieldSalary                                                    */
/***************************************************************************/
static errorType OnMinimalFieldSalary(void* DS, const char* const command) {
	int field;
	ValidateRead( sscanf(command, "%d",&field), 1, "MinimalFieldSalary failed.\n" );
	int	min;
	StatusType res = MinimalFieldSalary(DS,field,&min);
	
	if (res != SUCCESS) {
		printf("MinimalFieldSalary: %s\n",ReturnValToStr(res));
	}
	else {
		printf("MinimalFieldSalary: %s %d\n", ReturnValToStr(res),min);
	}

	return error_free;
}


/***************************************************************************/
/* OnAverageOfFirstKInField                                                */
/***************************************************************************/
static errorType OnAverageOfFirstKInField(void* DS, const char* const command) {
	int field;
	int k;
	ValidateRead( sscanf(command, "%d %d",&field,&k), 2, "AverageOfFirstKInField failed.\n" );
	double	average;
	StatusType res = AverageOfFirstKInField(DS,field,k,&average);
	
	if (res != SUCCESS) {
		printf("AverageOfFirstKInField: %s\n",ReturnValToStr(res));
	}
	else {
		printf("AverageOfFirstKInField: %s %f\n", ReturnValToStr(res),average);
	}

	return error_free;
}


/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	Quit(DS);
	if( *DS != NULL ) {
		printf("Quit failed.\n");
		return(error);
	};
	isInit = false;
	printf("Quit done.\n");

	return error_free;
}




#ifdef __cplusplus
}
#endif


