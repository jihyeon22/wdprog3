#ifndef __MDS_WATCHDOG_UTIL__
#define __MDS_WATCHDOG_UTIL__


#define MDS_WATCHDOG_DEV	"/dev/watchdog"

#define MDS_WATCHDOG_DEV_MAJOR_ID 10
#define MDS_WATCHDOG_DEV_MINOR_ID 99

#define MDS_WATCHDOG_INVAILD	-1
#define MDS_WATCHDOG_OK			1
#define MDS_WATCHDOG_NOK		0

#define MDS_WATCHDOG_RETRY_CNT	2
#define MDS_WATCHDOG_READ_DRV_INFO_RETRY_CNT	2
#define MDS_WATCHDOG_MAKE_DRV_NODE_RETRY_CNT	2

#define WD_MAX_BUFF_SIZE 		64
#define WD_MAX_WAIT_READ_SEC	1

// --------------------------------------------------------------
// --------------------------------------------------------------
#define IOCTL_GET_WATCHDOG_LOG               _IOR(MDS_DEVICE_UTIL_MAJOR_NUMBER, 12, char *)


// --------------------------------------------------------------
// command set
// --------------------------------------------------------------
#define MDS_WATCHDOG_CMD__CHECK					"WD$$WD_CHK" // no argument
// arg : no argument
// return : 
//  - WD_CHK:OK\r\n
 
#define MDS_WATCHDOG_CMD__ALL_DISABLE			"WD$$ALL_DISABLE"
// arg : no argument
// return : 
//  - ALL_DISABLE:OK\r\n

#define MDS_WATCHDOG_CMD__ALL_ENABLE			"WD$$ALL_ENABLE"
// arg : no argument
// return : 
//  - ALL_ENABLE:OK\r\n


#define MDS_WATCHDOG_CMD__LOG_SET				"WD$$LOG_SET"
// arg 1 : 0 or 1 
//    - 0 : log disable
//    - 1 : log enable
// return : 
//  - LOG_SET:OK,(%d)
//            1. set or not set

#define MDS_WATCHDOG_CMD__LOG_GET				"WD$$LOG_GET"
// arg : no argument
// return : 
//  - LOG_GET:OK\r\n

#define MDS_WATCHDOG_CMD__LOG_CLR				"WD$$LOG_CLR"
// arg : no argument
// return :
//  - LOG_CLR:OK\r\n

#define MDS_WATCHDOG_CMD__ALL_DISPLAY			"WD$$ALL_DISPLAY"
// arg : no argument
// return : 
//  - ALL_DISPLAY:OK,(%d)\r\n    ==> runwd count

#define MDS_WATCHDOG_CMD__WD_SET				"WD$$WD_SET"
// arg 1 : id     ==> id 로 최대 8자의 스트링
// arg 2 : time   ==> sec 단위로 최소 20 sec 이상
// return : 
//  - WD_SET:OK,%s\r\n 
//           1. setting id
//  - WD_SET:EROOR,%d\r\n  
//        ==> error reason
//            1 : argument invalid
//            2 : id lenth over
//            3 : argument invalid
//            4 : time argument is too small ( < 20sec )
//            5 : already use id

#define MDS_WATCHDOG_CMD__WD_CLR				"WD$$WD_CLR"
// arg : no argument
// return : no return

#define MDS_WATCHDOG_CMD__ID_RUN				"WD$$ID_RUN"
// arg 1 : id     ==> id 로 최대 8자의 스트링
// arg 2 : run_flag   ==> 0 : stop / 1 : run
// return : 
//  - ID_RUN:OK,%s\r\n 
//            1 : id
//  - ID_RUN:EROOR,%d\r\n  
//        ==> error reason
//            1 : argument invalid
//            2 : id lenth over
//            3 : argument invalid
//            4 : invlid wd id

#define MDS_WATCHDOG_CMD__GET_CFG				"WD$$GET_CFG"
// arg 1 : id     ==> id 로 최대 8자의 스트링
// return : 
//  - GET_CFG:OK,%s,%d,%d,%d\r\n 
//        ==> 1 : id
//        ==> 2 : run stat (0 :no /1: run)
//        ==> 3 : watchdog count
//        ==> 4 : watchdog reset sed

//  - GET_CFG:EROOR,%d\r\n  
//        ==> error reason
//            1 : argument invalid
//            2 : id lenth over
//            3 : argument invalid
//            4 : invlid wd id

#define MDS_WATCHDOG_CMD__SET_CFG				"WD$$SET_CFG"
// arg 1 : id     ==> id 로 최대 8자의 스트링
// arg 2 : time   ==> sec 단위로 최소 20 sec 이상
// return : 
//  - SET_CFG:OK,%s\r\n
//               1: id
//  - SET_CFG:EROOR,%d\r\n  
//        ==> error reason
//            1 : argument invalid
//            2 : id lenth over
//            3 : argument invalid
//            4 : time argument is too small ( < 20sec )
//            5 : id is invalid

#define MDS_WATCHDOG_CMD__SET_RES				"WD$$RES_SET"
// arg 1 : time   ==> sec 단위로 최소 1 sec 이상
// return : 
//  - RES_SET:OK,(%d)\r\n
//               1: time
//  - 무조건 리턴.. 0 일경우 기본값 10으로 강제세팅

#define MDS_WATCHDOG_CMD__GET_RES				"WD$$RES_GET"
// noargs
// return : 
//  - RES_GET:OK,(%d)\r\n
//               1: time
//  - 무조건 리턴.. 0 일경우 기본값 10으로 강제세팅



#define MDS_WATCHDOG_CMD__SPILT_CHAR		'\r'


// ------------------------------------------------------------
#define LOG_TARGET	NULL

#define WD_LOGD(msg...)        printf(msg)
#define WD_LOGW(svc,msg...)    printf(msg) // warning  : brown
#define WD_LOGI(svc,msg...)    printf(msg)    // info     : green
#define WD_LOGE(svc,msg...)    printf(msg)   // error    : red
#define WD_LOGT(svc,msg...)    printf(msg)   // trace    : brightmagenta
// ------------------------------------------------------------
int init_mds_watchdog();
int chk_mds_watchdog_support();

//static int _wd_util_isExistFile(char *file, int timeout);
//static int _wd_util_wait_read(int fd, unsigned char *buf, int buf_len, int ftime);

int wd_util_watchdog_set(char* wd_id, int wd_time);
int wd_util_watchdog_clr(char* wd_id);
int wd_util_watchdog_chk();
int wd_util_watchdog_all_disable();
int wd_util_watchdog_all_enable();
int wd_util_watchdog_all_display();
int wd_util_watchdog_log_set(int set);
int wd_util_watchdog_log_get();
int wd_util_watchdog_log_clr();
int wd_util_watchdog_id_run(char* wd_id, int run_flag);
int wd_util_watchdog_get_cfg(char* wd_id);
int wd_util_watchdog_set_cfg(char* wd_id, int stime);
int wd_util_watchdog_set_res(int res);
int wd_util_watchdog_get_res(int* res);

#endif
