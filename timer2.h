#ifndef _TIMER2_H_
#define _TIMER2_H_

//CH559 Timer2ʱ��ѡ��   
//bTMR_CLKͬʱӰ��Timer0&1&2,ʹ��ʱҪע��                                                       
#define mTimer2ClkFsys( )      {T2MOD |= (bTMR_CLK | bT2_CLK);C_T2=0;}         //��ʱ��,ʱ��=Fsys
#define mTimer2Clk4DivFsys( )  {T2MOD &= ~bTMR_CLK;T2MOD |=  bT2_CLK;C_T2 = 0;}//��ʱ��,ʱ��=Fsys/4
#define mTimer2Clk12DivFsys( ) {T2MOD &= ~(/*bTMR_CLK | */bT2_CLK);C_T2 = 0;}      //��ʱ��,ʱ��=Fsys/12
#define mTimer2CountClk( )     {C_T2 = 1;}                                     //������,T2���ŵ��½�����Ч

//CH559 Timer2 ��ʼ(SS=1)/����(SS=0)
#define mTimer2RunCTL( SS )    {TR2 = SS ? START : STOP;}


/*******************************************************************************
* Function Name  : mTimer2Setup(UINT8 T2Out)
* Description    : CH559��ʱ2��ʼ��
* Input          : UINT8 T2Out,�Ƿ�����T2���ʱ��
                   0�����������
                   1���������  
* Output         : None
* Return         : None
*******************************************************************************/
extern void mTimer2Setup(UINT8 T2Out);


/*******************************************************************************
* Function Name  : mTimer2Init(UINT16 Tim)
* Description    : CH559 T2��ʱ������ֵ                   
* Input          : UINT16 Tim,��ʱ����ֵ
* Output         : None
* Return         : None
*******************************************************************************/
extern void mTimer2Init(UINT16 Tim);


/*******************************************************************************
* Function Name  : T2exCaptureSetup(UINT8 mode)
* Description    : CH559��ʱ������2 T2EX���Ų�׽���ܳ�ʼ��
                   UINT8 mode,���ز�׽ģʽѡ��
                   0:T2ex���½��ص���һ���½���
                   1:T2ex�������֮��
                   3:T2ex�������ص���һ��������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
extern void T2exCaptureSetup(UINT8 mode);


/*******************************************************************************
* Function Name  : T2CaptureSetup(UINT8 mode)
* Description    : CH559��ʱ������2 T2���Ų�׽���ܳ�ʼ��T2
                   UINT8 mode,���ز�׽ģʽѡ��
                   0:T2ex���½��ص���һ���½���
                   1:T2ex�������֮��
                   3:T2ex�������ص���һ��������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
extern void T2CaptureSetup(UINT8 mode);

#endif

