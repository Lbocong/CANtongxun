#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "CAN.h"
#include "pid.h"

CanRxMsg RxMessage;
uint8_t flag = 0;
CanTxMsg    CAN_Tran_Data;
 
void Delay(__IO uint32_t nCount); 

int main(void)
{ 	

	Serial_Init();
	printf("\r\n 这是一个CAN单板通讯实验 \r\n");
	
	CAN_Config();
//	RECIVE_CAN(&RxMessage);
	while(1)
	{	
			uint8_t box;
			
			CAN_Tran_Data.StdId = 0;
			//CAN_Tran_Data.ExtId = PASS_ID;
			CAN_Tran_Data.RTR = CAN_RTR_Data;
			CAN_Tran_Data.IDE = CAN_Id_Standard ;
			CAN_Tran_Data.DLC = 1;
		    CAN_Tran_Data.Data[0] = 10;
			
			box = CAN_Transmit(CAN1,&CAN_Tran_Data);
			
			while(CAN_TransmitStatus(CAN1,box) == CAN_TxStatus_Failed);

          	    printf(" 数据包发送完成\n");
            Delay_s(1);
		 	
		if(flag == 1)
		{
				printf("接收到的数据：%d\n",RxMessage.Data[0]);
			  flag = 0;
		}
	}
}

//void Delay(__IO uint32_t nCount)
//{
//  for(; nCount != 0; nCount--);
//}


