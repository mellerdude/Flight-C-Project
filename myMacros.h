#pragma once

#define CHECK_RETURN_0(x) (x==NULL) ? 0 : 1
#define CHECK_RETURN_NULL(x)(x==NULL) ? NULL
#define CHECK_MSG_RETURN_0(x) (x==NULL)?printf("Error\n"):0
#define CHECK_0_MSG_CLOSE_FILE(x)(x==0)?printf("Error\n")\fclose(x)\0
#define CHECK_NULL__MSG_COLSE_FILE(x)(x==NULL)?printf("Error\n")\fclose(x)\0
#define MSG_CLOSE_RETURN_0 printf("Error\n")\fclose(x)\0
