
#ifndef _GPIO_H_
#define _GPIO_H_

/*******************************************************************************
* Function Name  : CH554GPIODrivCap(UINT8 Port,UINT8 Cap)
* Description    : �˿�0��1��2��3������������
* Input          : UINT8 Port�˿�ѡ��(0��1��2��3)
                   UINT8 Cap��������ѡ��((0)5mA��(1)20mA(ע��:P1����10mA))
* Output         : None
* Return         : SUCCESS�ɹ�
                   FAILʧ��
*******************************************************************************/
extern UINT8 CH554GPIODrivCap(UINT8 Port,UINT8 Cap);


/*******************************************************************************
* Function Name  : CH554GPIOModeSelt(UINT8 Port,UINT8 Mode,UINT8 PinNum)
* Description    : �˿�0��1��2��3����ģʽ����
* Input          : UINT8 Port�˿�ѡ��(0��1��2��3)
                   UINT8 Cap������ʽѡ��(bPn_OC & Pn_DIR & Pn_PU)
                   0(000)�������룬��������
                   1(001)�������룬��������
                   2(01x)������������ߵ͵�ƽǿ������
                   3(100)����©�������������֧�����룻
                   UINT8 PinNum(����ѡ��0-7)
* Output         : None
* Return         : SUCCESS�ɹ�
                   FAILʧ��
*******************************************************************************/
extern UINT8 CH554GPIOModeSelt(UINT8 Port,UINT8 Mode,UINT8 PinNum);


#endif

