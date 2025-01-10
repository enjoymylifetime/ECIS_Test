#ifndef COMMON_H
#define COMMON_H

#define		OPEN				1
#define		CLOSE				0

#define	RatioConstant			0				//斜率恒定
#define	TimeConstant			1				//时间恒定

#define		ThreeAxis			0				//三轴
#define		FourAxis			1				//四轴
#define		FiveAxis			2				//五轴

#define		TRUE					1
#define		OK						1
#define		COMPLETE				1	
#define		FALSE					0
#define		NOT_COMPLETE			0


//#define 	STDGCODE_MOD			10
#define 	SPCGCODE_MOD			10

// 运动控制
#define		MovePositive		1				// 正向移动
#define		MoveNegtive			0				// 负向移动

//CH0603
#define 	StaticTrackLimit		0.5		//静态轨迹判定界限0.5mm  CH0603
#define 	Max_StaticErrorTimes 	1000	//静态轨迹判定周期约1s

#define  	REF_XYZ			0	//坐标系为3 坐标
#define  	REF_XYZA		1	//坐标系为3+A 坐标
#define  	REF_XYZB		2	//坐标系为3+B 坐标
#define  	REF_XYZC		3	//坐标系为3+C 坐标

#define  	INTERPOLATIONBUFLENGTH 				40	//STD插补缓冲区
#define  	SPC_INTERPOLATIONBUFLENGTH 			40	//SPC插补缓冲区


typedef struct
{
	s32 X;
	s32 Y;
	s32 Z;
	s32 A;
}INT40AXIS;     

typedef struct
{
	u32 X;
	u32 Y;
	u32 Z;
	u32 A;
}UINT40AXIS;     

typedef struct
{
	u16 X;
	u16 Y;
	u16 Z;
	u16 A;
}UINT16AXIS;     

typedef struct
{
	s16 X;
	s16 Y;
	s16 Z;
	s16 A;
}INT16AXIS;     

typedef struct
{
	u8 X;
	u8 Y;
	u8 Z;
	u8 A;
}UINT8AXIS;   

typedef struct
{
	s8 X;
	s8 Y;
	s8 Z;
	s8 A;
}INT8AXIS;   

typedef struct
{
	double X;
	double Y;
	double Z;
	double A;
}FLOAT64AXIS;     

typedef struct
{
	float X;
	float Y;
	float Z;
	float A;
}FLOAT32AXIS;     

typedef struct
{
	double X;
	double Y;
	double Z;	
	double A;
}VECTOR;     //所定义都为单位矢量


// AREA_CONTROL  用于多段代码加减速连续处理
// 用于A4 A5 SPINDLE 轴计算时速度单位(degree/s), 距离单位(degree)
typedef struct
{
	//区域相关变量
	u32		Pointer_StartCode;				//分解代码，区域起始代码段指针
	u32		Pointer_EndCode;				//分解代码，区域终止代码段指针
	double	Ss;								//向后线段搜索距离(mm)
	double	Stotal;							//区域内所有代码总运行长度 mm
	double	CurrentStotal;					//从区域起点代码到当前代码终点总运行长度 mm
	double	CurrentStotalLast;				//从区域起点代码到当前代码起点总运行长度 mm
	double 	Snow;							//从区域起点代码到当前代码当前插补点总运行长度 mm  
	double 	SnowOut;						//加入前馈后从区域起点代码到当前代码当前插补点总运行长度 mm  
	double 	DeltaSnow;						//从当前代码起点到当前代码当前插补点总运行长度 mm  

	double	DeltaSKp;					//
	double	DeltaSKv;					//
	
	u32	       I;					//插补序号 [1,+无穷)
	u32 	      TotalN;				//总插补数	TotalN=T5/Tsample
	double	Vs;					//当前运行G代码起点运行速度. (mm/s)
	double	Vm;					// 当前运行G代码设定运行速度. (mm/s)
	double	VmReal;				// 当前运行G代码实际最高运行速度. (mm/s)
	double	Ve;					// 当前运行G代码终点运行速度. (mm/s)
	double 	VNow;				// 当前实际运行速度. (mm/s)
	double 	VNowOut;			// 当前实际指数化输出运行速度. (mm/s)
	double 	VMin;				// 当前最小运行速度. (mm/s)
	u16 		VChangeSign;		//速度档变化标志，需重新计算加减速曲线
	double 	SnowLast;			//当前代码上次插补总运行长度 mm  
	double	Sac;				//当前代码加速过程所需距离(mm)
	double	Sm;					//当前代码稳速过程所需距离(mm)
	double	Sde;				//当前代码减速过程所需距离(mm)
	double	S1;					//抛物线AB积分面积 mm
	double	S2;					//抛物线BC积分面积 mm
	double	S3;					//直线CD积分面积 mm
	double	S4;					//抛物线DE积分面积 mm
	double	S5;					//抛物线EF积分面积 mm
	double	S6;					//抛物线EF积分面积 mm
	double	S7;					//抛物线EF积分面积 mm
	double	S8;					//抛物线EF积分面积 mm
	double	S9;					//抛物线EF积分面积 mm

	double	T1;					//从A到B所用时间	s
	double	T2;					//从A到C所用时间	s
	double	T3;					//从A到D所用时间	s
	double	T4;					//从A到E所用时间	s
	double	T5;					//从A到F所用时间	s
	double	T6;					//从A到F所用时间	s
	double	T7;					//从A到F所用时间	s
	double	T8;					//从A到F所用时间	s
	double	T9;					//从A到F所用时间	s

	double	DeltaT1;			//AB所用时间	s
	double	DeltaT2;			//BC所用时间	s
	double	DeltaT3;			//CD所用时间	s
	double	DeltaT4;			//DE所用时间	s
	double	DeltaT5;			//EF所用时间	s
	double	DeltaT6;			//EF所用时间	s
	double	DeltaT7;			//EF所用时间	s
	double	DeltaT8;			//EF所用时间	s
	double	DeltaT9;			//EF所用时间	s
	
	double	a_ac;			// 实际加速段加速度		
	double	a_de;			// 实际减速段加速度

	double	Acc_ac1;				// 实际加速段加速度		
	double	Acc_ac2;				// 实际加速段加速度		
	double	Acc_ac3;				// 实际加速段加速度		
	double	Acc_ac4;				// 实际加速段加速度		

	double	Acc_de1;				// 实际减速段加速度
	double	Acc_de2;				// 实际减速段加速度
	double	Acc_de3;				// 实际减速段加速度
	double	Acc_de4;				// 实际减速段加速度
	
	double 	Tao_ac;				//实际加速段时间常数Tao		s
	double 	Tao_de;				//实际减速段时间常数Tao		s	
	
	double 	Tao_ac_line;			//斜率型算法实际加速段时间常数Tao		s
	double 	Tao_de_line;			//斜率型算法实际减速段时间常数Tao		s
	
	double 	Tao_ac_1;			//实际加速段1时间常数Tao1		s
	double 	Tao_ac_2;			//实际加速段2时间常数Tao2		s
	double 	Tao_ac_3;			//实际加速段3时间常数Tao3		s
	double 	Tao_ac_4;			//实际加速段4时间常数Tao4		s

	double 	Tao_de_1;			//实际减速段1时间常数Tao1		s
	double 	Tao_de_2;			//实际减速段2时间常数Tao2		s
	double 	Tao_de_3;			//实际减速段3时间常数Tao3		s
	double 	Tao_de_4;			//实际减速段4时间常数Tao4		s
	
	double	Vclamp;				// G1切削钳制速度. (mm/s)
	double	Vclamp1;			// 钳制速度1.(攻牙时主轴钳制速度1换算到Z轴钳制速度1.) (mm/s)
	double	Vclamp2;			// 钳制速度2.(攻牙时主轴钳制速度2换算到Z轴钳制速度2.) (mm/s)
	double	Vclamp3;			// 钳制速度3.(攻牙时主轴钳制速度3换算到Z轴钳制速度3.) (mm/s)
	double	Vclamp4;			//钳制速度4.(攻牙时主轴钳制速度4换算到Z轴钳制速度4.) (mm/s)

	double		CurrentT;			// 当前插补时间  I*Tsample	unit:s
	VECTOR		Cosine;				// 插补轴方向夹角余弦
	INT40AXIS	DeltaStep;			// 直线中每段x应走距离  unit:pulse(输出指令单位)
	INT40AXIS	DeltaStep_Bak;		// 暂存直线中每段x应走距离  unit:pulse(输出指令单位)
	double 		CurrentArcAngle;	//当前插补周期圆弧插补的角度值(单位:弧度)
	INT40AXIS	NowValue;			// 当前插补点坐标位置值--最小输入单位
	INT40AXIS	OldValue;			// 前一插补点坐标位置值--最小输入单位

	INT40AXIS	NowPointMACHPulseOut;	// 当前插补点MACH 坐标逆补偿输出位置值(最小输入单位)
	INT40AXIS	OldPointMACHPulseOut;	// 前一插补点MACH 坐标逆补偿输出位置值(输出指令单位)
	INT40AXIS	EndPointMachPulseOut;	// 当前代码终点MACH 坐标逆补偿输出位置值(输出指令单位)
	INT40AXIS	NowPointMACHPulseOutA4;
	INT40AXIS	OldPointMACHPulseOutA4; 

	u16                 DelayTime;      //走完以后延迟数

	// 单段功能用
	INT40AXIS	SingleAddLineOldPoint;	// 单段节点绝对位置，用于恢复位置 单位:最小输入单位

	u16		SpeedState;					//区域速度状态
	u16		SpeedStateCal;				//观察区域速度状态计算出口。
	u16		ZeroPulseSign;				//零脉冲标志,1为零脉冲

}AREA_CONTROL;

//CH0512
typedef struct
{
	u32 		 	SendCount;			//DSP当前运行原代码位置指针，返回给ARM用于显示及其它用途
	u16 			CMD1;			       //命令字,确定G代码类型0 G0  1  G1   2 顺弧 3 逆弧
	u16            	CMD2;                         //0  PTP模式 1  CP模式
	INT40AXIS	StartPoint;			 //起点. 单位：线性轴最小输入单位
	INT40AXIS	EndPoint;			 //终点.  单位：线性轴最小输入单位
	INT40AXIS	CenterPoint;		        //圆心点 .单位：线性轴最小输入单位
	FLOAT64AXIS	DeltaPoint,RoatStartPoint,RoatEndPoint,DelatVec;	//起点与终点的相对距离 单位: mm  
	double 		StartAngle;			//起始角度.单位: 弧度(传输单位：旋转轴最小输入单位)
	double 		EndAngle;			//终止角度.单位: 弧度(传输单位：旋转轴最小输入单位)
	double		currentAngle; 		//当前角度.单位: 弧度(传输单位：旋转轴最小输入单位)
	u16 			GGroup02;			//平面组群选择 G17(defaut) G18 G19
	u16 			GGroup15;			//准停模态选择  G61 G64(defaut)
	FLOAT64AXIS	ScaleCoefficient;  	//比例缩放系数。一般情况下为1。
	INT40AXIS	ScaleCenter;		       //比例缩放圆心点 .单位：线性轴最小输入单位
	double 		Stotal,SL;			//当前G代码长度  单位:mm   正值
	double 		Feedrate;			//进给速度,单位:mm/s
	double 		Vm;					//根据档位确定的理论进给速度,单位:mm/s
	double 		Ve;					//终点允许速度,单位:mm/s
	double 		Vveer;				//起点拐点处允许进给速度  单位：mm/s
	s32			Radius;				//园弧半径 单位：线性轴最小输入单位
	VECTOR  	StPointVector;		//直线或圆弧起点余弦矢量值
	VECTOR  	EndPointVector;		//直线或圆弧终点余弦矢量值
	u16			MoveCodeSign;		//运动代码标志,0为非运动代码，1为XYZ运动代码,2为A4运动代码
	u16			VeCalSign;			//Ve已计算标志
	double		cosangle;			//相邻线段夹角余弦值
	s16 			AxisMotionStyle;		//0：A4轴不运行，1：A4轴运行。3:单段加线第三步IV轴单独运行；4:IV轴单独SPC	
}GCODE;


//0 停止模式 1  找原点  2  JOG    3  操纵杆运动  4  探针  5   点位运动
#define  STOPMODE       0
#define  FINDORI           1
#define  JOGMODE          2
#define  JOYMODE          3
#define  PROBEMODE      4
#define  POSMOVE          5


//总体标志和变量用结构体
typedef struct
{
	u16 		NCSign;  	// 0:通常状态  1:标准代码；2:特殊代码-JOG HANDLE REF；INI=0

	//速度控制相关参数
	u16		LastFeedrateOverride;		//上次进给速度档位
	u16		LastRapidFeedrateOverride;	//上次快进速度档位
	u16 		FeedrateOverride;			//进给档位	[0-20]
	u16 	 	RapidFeedrateOverride;		//G0快速进给档位	[0-20]
	u16 		FeedrateOverride_Bak;		//暂存进给档位	[0-20]
	u16 	 	RapidFeedrateOverride_Bak;	//暂存G0快速进给档位	[0-20]	
	//CH0506 GCODE	LastMoveGCode;			//暂存上条发送运动G代码结构内容
	GCODE	STDLastMoveGCode;			//暂存上条发送运动G代码结构内容
	GCODE	SPCLastMoveGCode;			//暂存上条发送运动G代码结构内容
	VECTOR	LastMoveCodeEndVector;		//上一条运动G代码终点方向矢量(代码预处理用)
	u16		EveryAxisCoinValid;			// 各轴COIN 都有效标志
	u16		EveryAxisOverValid;			// 各轴OVER 都有效标志

	// 坐标跟踪相关参数
	u16 		GetMachCoordinateRight;		//  1:获得机床坐标正确
		
	INT40AXIS	ABS_Coordinate;				// 脉冲        当前绝对坐标值unit:最小输入单位
	INT40AXIS	ABSORG_M_Coordinate;		// 当前绝对坐标原点的机床坐标值unit:最小输入单位
	UINT16AXIS	MoveSign;					// 当前运动方向1-positive 0-negtive 
	UINT16AXIS	TheoryMoveSign;			// 当前代码理论方向1-positive 0-negtive 

	INT40AXIS	MYORG_M_Coordinate;		// 名义坐标原点的机床坐标值unit:最小输入单位
	INT40AXIS	ABS_MY_OffsetCoordinate;	// 工件绝对坐标相对名义坐标偏移坐标值unit:最小输入单位
	INT40AXIS	ABS_MY_ORG_RotationOffsetCoordinate;	// 工件绝对坐标原点相对名义坐标原点旋转偏置坐标值unit:最小输入单位
	INT40AXIS	ABS_OffsetCoordinate;		// 工件绝对坐标G52 偏移坐标值unit:最小输入单位
	INT40AXIS	ABS_OffsetCoordinateBak;	// 工件绝对坐标G52 偏移坐标值unit:最小输入单位
	double		COS_A4;						// A4  余弦值
	double		SIN_A4;						// A4  正弦值

	//上条运动代码指针  CH0601
	u16		LastCodeOverSign;			//最后一条代码走完标志  1－走完

	INT40AXIS	GapCompensateCnt;			//反向间隙补偿标志

	//波折线段判定  CH0508
	UINT16AXIS	LastTheoryMoveSign;			// (代码预处理用)上一代码理论方向1-positive 0-negtive 


	u16		Int4IdleSign;					//中断4 空闲标志

	u32		InterpolationSendCnt;		//缓冲区发送条数
	u32		InterpolationRunCnt;		       //缓冲区运行条数
	UINT16AXIS	SearchRefMoveSign;	       //参考点查找方向。1：负向；2：正向
	u16		BFChageOverrideSpeedSign;	//减速箱变档标志
	u8		RapidAccelerateStyle;		//快进加减速类型.0:(默认) 斜率恒定加减速；1:时间恒定加减速
	u8		UsualAccelerateStyle;			//切削加减速类型.0:(默认) 斜率恒定加减速；1:时间恒定加减速
	u8		HardLimitValid;				//硬限位触发
	u8		HardLimitInvalid;			//硬限位无触发
	u8		InputValid;					//输入信号触发
	u8		InputInvalid;				//输入信号无触发
	u8		OutputValid;					//输出信号触发
	u8		OutputInvalid;				//输出信号无触发
	u8		HardLimitNeedGetPositionSign;     //撞了限位，防止位置错，需要重新找参考点


       u8           WorkMode;       //0 停止模式 1  找原点  2  JOG    3  操纵杆运动  4  探针  5   点位运动
       u8           JogSign:1;        //  0    1 Jog中
       double     FeedRate;        //进给速度,单位:mm/s
}OVERALLSIGN;


typedef struct
{
   INT40AXIS MachCoor;             //机床坐标:脉冲数  直接从编码器出来的坐标
   INT40AXIS MyMachCoor;         //用户机床坐标:脉冲数，为机床进行偏移后的坐标
   INT40AXIS MachCoorOffset;    //机床坐标偏移:MyMachCoor=MachCoor+MachCoorOffset
   FLOAT64AXIS AbsRotateCoor;    //旋转坐标:X,Y,Z,A均位旋转角度
   FLOAT64AXIS AbsCarteCoor;      //笛卡尔直角坐标 X，Y，Z毫米，A，度
}COORDINATE;

typedef struct
{
  double   PoleOneLength;        //杆1长度
  double   PoleTwoLength;        //杆2长度
  
}SCARAPAR;

typedef struct
{	
	UINT16AXIS	EncoderCheckChoose;	//P000-P005监测轴光栅尺标志	
	u16		       SlaveMAX;				       //P014 伺服总线最大从站数目
	double		Tsample;				//P020单位：s   设定插补周期 [0.1,10]ms ,传输对应[1,100]
	double		Tsample1;				//单位：s   设定插补周期， 用于中断程序中  考虑停用	
	FLOAT64AXIS	MAXSpeed;				//P021-P023各轴最大移动速度 单位:mm/s	 or degree/s
	//P024-P029
	u16		A4_Model;						//A4 轴模型选择0-无效1-A 2-B 3-C
	u16		A4_HardLimitValidSign;			//A4 轴硬限位有效标志 1-有效

	double	VeerDeltaV;				//DSPb0-32拐点单轴变化速度(unit:mm/s)  设定范围[1,25.5] 传输对应[1-255] 
	double	NicetyVeerDeltaV;		//DSPb0-33精准转向拐点单轴变化速度(unit:mm/s)  设定范围[1,25.5]传输对应[1-255] 
	u32 		TrackRunOutRangeSQR;	//DSPb0-34轨迹偏离报警范围(平方)  unit:mm.mm  
	u8		FunctionSelectionSwitch_1;		
	double	FlexuousAxisLength;		//DSPb0-36曲线平滑允许误差/线段单轴最大波折长度unit:mm
	double	ArcFeedDownRatio;		//DSPb0-37圆弧减速比[0,25.5] 传输对应[0,255] 0时无效
	double	VeerDeltaT; 				//DSPb0-38转向过程时间常数 （单位：s）    设定范围[1,255]ms 传输对应[1-255]
	double	NicetyVeerDeltaT;  		//DSPb0-39精准转向过程时间常数（单位：s）  设定范围[1,255]ms 传输对应[1-255]
	double 	ArcDownRatio;			//DSPb0-40圆弧定速
	u8		FunctionSelectionSwitch_2;		//P050	功能选择开关2
	//0	默认五次方S形加速
	//1:五次方曲线
	//2:线性加减速曲线
	//4:软指数加减速曲线
	//5:硬指数加减速曲线
	
	//bit 5 (&0x10)reserved
	//bit 6 (&0x20)reserved
	//bit 7 (&0x40)reserved
	//bit 8 (&0x80)reserved
	u8  		AreaControlModle;				
	//0:默认二次方S曲线
	// 1:五次方曲线
	// 2:线性加减速曲线
	// 4:软指数加减速曲线
	//5:硬指数加减速曲线
	//6:(4段)线性组加减速曲线
	//7:伺服主轴攻牙(保留参数测试用)
	
	//bit5 (&0x10)开启自由组合算法
	//bit6 (&0x20)
	//bit7 (&0x40)切削模态加减速类型。	0:(默认) 斜率恒定加减速；1:时间恒定加减速
	//bit8 (&0x80)G0模态加减速类型。		0:(默认) 斜率恒定加减速；1:时间恒定加减速
	
	u8		FunctionSelectionSwitch_3;		//P052	功能选择开关3								
	//0	默认五次方S形减速
	//1:五次方曲线
	//2:线性加减速曲线
	//4:软指数加减速曲线
	//5:硬指数加减速曲线
	
	//bit 5 (&0x10)reserved
	//bit 6 (&0x20)reserved
	//bit 7 (&0x40)reserved
	//bit 8 (&0x80)reserved
	
	u16		SpindleSpeedbackmodle;			//P53刚性攻丝主轴速度反馈采集模式(0 : VT总线,1:编码器)
	u16		HardLimitFilterTime;				//P54硬限位时间常数.uint:ms
	u16		SCIB_NoCom_Count;				//P55主轴连续不通讯次数。单位：S。

	u8		FunctionSelectionSwitch_4;		//P56功能选择开关4
	//bit 1 (&0x01)SPC平摊。0:平摊;1:不平摊
	//bit 2 (&0x02)通用主轴实际速度未达到设定速度最低限则进给暂停
	//bit 3 (&0x04)反向间隙平摊。0:不平摊;1:平摊(用于大反向间隙的硬轨机床)
	//bit 4 (&0x08)
	//bit 5 (&0x10)STD平摊。0:平摊;1:不平摊
	//bit 6 (&0x20)攻牙时主轴档位受控(一般为不受控,只有0和10档)
	//bit 7 (&0x40)自动上下料电机找参考点运行方式
	//bit 8 (&0x80)自动上下料电机SPC加速度设置为149。
	
	u8		FunctionSelectionSwitch_5;		//P57功能选择开关5(主要用于测试)
	//bit 1 (&0x01)测试伺服攻牙时间
	//bit 2 (&0x02)测试伺服攻牙转速
	//bit 3 (&0x04)监控 双驱同步误差
	//bit 4 (&0x08)
	//bit 5 (&0x10)
	//bit 6 (&0x20)显示伺服刀盘工位角度值
	//bit 7 (&0x40)ARM与DSP通讯不成功达到次数后复位。0:复位;1:不复位
	//bit 8 (&0x80)外接急停报警输入信号线

	double	ExponentMaxSpeed;				//065 运动控制指数化最大速度 unit:mm/s [0,100]
	double	ExponentMinRatio;				//066 运动控制指数化最小减速比率  [0.1,0.9] 
	double	Vnow_TsampleLinearMaxSpeed;	//065	线性化减速最大速度	unit:mm/s [0,100]
	u32		Vnow_TsampleLinearRatio;		//066	线性化减速比率			  [1,9] 
	double	SPCShakeSign;					//067	SPC shake	手动速度减速比率；  [0.8,1.0] 
	double	STDShakeSign;					//068	SPC shake	自动速度减速比率；  [0.8,1.0] 	
	u8		FunctionSelectionSwitch_6;		//P69
	//bit 1 (&0x01)reserved
	//bit 2 (&0x02)区域5算法时间常数参数设置。默认0:P200(P199);	1:P204,P205
	//bit 3 (&0x04)区域5算法时间常数参数设置。默认0:加速减速都为P200	。1:加速时间P199,减速时间为P200。
	//bit 4 (&0x08)
	//bit 5 (&0x10)插补条过少时，不返回，直接GotoRunModle重新计算一次插补
	//bit 6 (&0x20)第二种情况:已到达当前代码终点，不返回，直接GotoPrecalculate
	//bit 7 (&0x40)SPC区域终点插补方式。置1:终点插补，不转入下一区域；默认0:终点不插补，转入下一区域
	//bit 8 (&0x80)
	
	u8		FunctionSelectionSwitch_7;		//P70
	//bit 1 (&0x01)工进速度显示作假
	//bit 2 (&0x02)主轴转速显示作假
	//bit 3 (&0x04)STD不够减速距离0:反算;1:不反算.
	//bit 4 (&0x08)SPC不够减速距离0:反算;1:不反算.
	//bit 5 (&0x10)置1:反算速度1.5倍
	//bit 6 (&0x20)置1:VeAfter速度1.2倍
	//bit 7 (&0x40)置1:向后搜索距离1倍;默认0:向后搜索距离2倍。
	//bit 8 (&0x80)限位对刀仪等输入信号作假(测试平台作假)
	
	u8		FunctionSelectionSwitch_8;		//P71
	//bit 1 (&0x01)外接C相作为找参考点信号
	//bit 2 (&0x02)SPC区域选择。置1:由P50,P51,P52参数设置；默认0:只有二次方S曲线
	//bit 3 (&0x04)SPC加速度不恒定为500
	//bit 4 (&0x08)区域6(四段)也指数化;0:不指数化
	//bit 5 (&0x10)硬限位开关信号高低电平切换
	//bit 6 (&0x20)DSPIN1~IN8输入信号高低电平切换
	//bit 7 (&0x40)DSPOUT1~OUT8输出信号高低电平切换
	//bit 8 (&0x80)reserved
	
	u8		FunctionSelectionSwitch_9;		//P72
	//bit 1 (&0x01)reserved
	//bit 2 (&0x02)置1:转弯角度计算时加速度恒定4000mm/s^2
	//bit 3 (&0x04)置1:按转角公式计算转弯速度；默认0:转弯角度小于VeerMinAngleValue转角减速最小角度时不减速
	//bit 4 (&0x08)区域6转弯角度计算时加速度选择.置1取 P149；默认0:取第一段加速度值,即P206/P210
	//bit 5 (&0x10)区域6由终点条反算速度方法选择.置1为直接用第一段线性反求
	//bit 6 (&0x20)速度前馈补偿功能
	//bit 7 (&0x40)置1:SPC最大加速度限制为3000
	//bit 8 (&0x80)打开前馈功能
	
	u8		FunctionSelectionSwitch_010;		//P73	
	//bit 1 (&0x01)变频器零伺服使能标志测试.0：零伺服使能无效1：零伺服使能有效
	//bit 2 (&0x02)置1:全部运动代码进行变档过滤;0(默认)G0代码进行变档过滤。
	//bit 3 (&0x04)对刀仪判断用
	//bit 4 (&0x08)置1:不过滤大直径小夹角圆弧;0(默认)过滤大直径小夹角圆弧
	//bit 5 (&0x10)置1:不过滤圆弧计算值小于直线距离代码;0(默认)过滤圆弧计算值小于直线距离代码
	//bit 6 (&0x20)置1:不过滤圆弧小于0.003mm距离代码;0(默认)过滤圆弧小于0.003mm距离代码
	//bit 7 (&0x40)置1:线性化(软启动)
	//bit 8 (&0x80)置1:不指数化

	
	u8		FunctionSelectionSwitch_011;		//P79
	//bit 1 (&0x01)reserved
	//bit 2 (&0x02)H2；默认0:接收代码双驱异步ServoRun_TwoServoAsynch;	1:双轴运动差值小于0.003mm时，ServoRun_TwoServoSynch同步。
	//bit 3 (&0x04)H2；默认0:AREAControl->DeltaStep.SYNC大于1mm，OverallSign.InterpolationPlusCnt_OneTsample = 20；1:插补量过大报警
	//bit 4 (&0x08)1:4轴锁紧/松开反馈开关
	//bit 5 (&0x10)1:4轴零点反馈
	//bit 6 (&0x20)1:齿轮箱档1
	//bit 7 (&0x40)1:齿轮箱档2
	//bit 8 (&0x80)1:主轴零点
	
	double 	BowstringError_Max; 		//P84	弓高误差最大值(Uint:um)
	double 	ToleranceStotalquotiety;		//P85	拟合曲线公差长度比例因子[10,100](uint:%)	
	u8		FunctionSelectionSwitch_012;	//P86
	
	u8		VeerMinAngle;				//P87转角减速最小角度

	double	ForwardFeedbackKp;			//位置前馈
	double	ForwardFeedbackKv;			//速度前馈

	u16	       RunState;					       //P119--运行状态设置－实时运行调试用  CH0903
										//0: 正常运行; 1: 不输出脉冲运行; 2:非中断脉冲输出
	
	//P120-P125
	u32 		LinearAxisMinUnit;			//线性轴最小输入单位(单位：nm)
	u32		RotaryAxisMinUnit;			//旋转轴最小输入单位(单位：nd)
	u32		SpindleAxisMinUnit;			//主轴最小输入单位(单位：nd)
	u32		LinearAxisOutUnitEQU;		//线性轴输出指令单位当量(单位：nm/指令单位)
	u32		RotaryAxisOutUnitEQU;		//旋转轴输出指令单位当量(单位：nd/指令单位)
	double 		UnitTo_mm;					//线性轴位置单位换算成mm   单位:  mm/unit
	double 		UnitTo_d;					//旋转轴位置单位换算成d	    单位:  d/unit


	UINT40AXIS	Gap;						//P137-P142 轴间隙值,单位: 最小输入单位
	UINT40AXIS	GapPulse;					// 轴间隙值,单位: 输出指令单位	
	double 		a_SET;						//P149根据速度重计算运动平台加速度 单位：mm/s.s
	double 		a_SET_ARM;					//ARM 设定运动平台加速度 单位：mm/s.s    	
	double 		Vclamp_SPC;				//P152 			SPC模态最大(快进三档进给速度)
	double 		SRefSpeed;					//P153 			参考点正向搜索速度，单位:mm/s
	double 		SRefSpeedBack;				//P154 			参考点返回速度，单位:mm/s
	s32 		       SRefBack;					//P153			参考点返回距离，单位:最小输入单位
	s32 		       SRefBackX;					//P153			参考点返回距离，单位:最小输入单位
	s32 		       SRefBackY;					//P153			参考点返回距离，单位:最小输入单位
	s32 		       SRefBackZ;					//P153			参考点返回距离，单位:最小输入单位
	double 		a_A4_SET;			 		//P165			设定A4 轴运动平台加速度 单位：degree/s.s    
   
	double 		A4SRefSpeed;				//P170
	double 		A4SRefSpeedBack;			//p171
	u32 		       A4SRefBack;					//p172
	double		A4_G0Speed;				//P173			A4 轴G0速度 degree/s

	FLOAT64AXIS	PosingSpeed;				//P175	定位速度degree/s
	FLOAT64AXIS	SearchREFSpeed;			//P179	找参考点速度上位degree/s 转化为r/min
	FLOAT64AXIS	SearchREFSpeedBack;		//P180	找参考点回退速度上位degree/s 
	FLOAT64AXIS	SearchREFDistanceBack;		//P181	找参考点回退距离上位degree

	
	double 		a_SET_ARM_Nicety;			//P195ARM 设定精准运动平台加速度 单位：mm/s.s    
	double 		a_SET_ARM_G0;				//P197ARM 设定精准G0运动平台加速度 单位：mm/s.s    

	//P198-200
	double	ExponentTimeConstant_Nicety;	//P198(指数型算法)电机机械时间常数单位0.1ms
	double	ExponentTimeConstant_ac;		//P199(指数型算法)电机机械时间常数单位*0.1ms
	double	ExponentTimeConstant_de;		//P200(指数型算法)电机机械时间常数单位*0.1ms

	//P203-205
	double	Vclamp;						//(斜线型算法)切削加工最大钳制速度mm/min->mm/s
	double	TimeConstant_ac;			//(斜线型算法)加速时间常数1.单位*0.1ms
	double	TimeConstant_de;			//(斜线型算法)加速时间常数1.单位*0.1ms

	//P206-213
	double	Vclamp1;			//切削加工钳制速度1...mm/min->mm/s...uint:(mm/s)
	double	Vclamp2;			//切削加工钳制速度2...mm/min->mm/s...uint:(mm/s)
	double	Vclamp3;			//切削加工钳制速度3...mm/min->mm/s...uint:(mm/s)
	double	Vclamp4;			//切削加工钳制速度4(最大钳制)...mm/min->mm/s...uint:(mm/s)

	double	TimeConstant1_ac;			//(运动轴加速)时间常数1.单位*0.1ms
	double	TimeConstant2_ac;			//(运动轴加速)时间常数2.单位*0.1ms
	double	TimeConstant3_ac;			//(运动轴加速)时间常数3.单位*0.1ms
	double	TimeConstant4_ac;			//(运动轴加速)时间常数4.单位*0.1ms

	//P214-217
	double	TimeConstant1_de;			//(运动轴减速)时间常数1.单位*0.1ms
	double	TimeConstant2_de;			//(运动轴减速)时间常数2.单位*0.1ms
	double	TimeConstant3_de;			//(运动轴减速)时间常数3.单位*0.1ms
	double	TimeConstant4_de;			//(运动轴减速)时间常数4.单位*0.1ms

	u16	PWM_PeriodRegister_MIN;			// PWM  最小写入值
	u16	PWM_PeriodRegister_MAX;			// PWM  最大写入值
	u16	PWM_PeriodRegister_ZeroPeriod;		// LPM为0时PWM  写入值
	//P203-P205
	FLOAT64AXIS	VFF_Ratio;						//各轴速度前馈比例系数
	
	u16	MachineConfiguration;				
       UINT16AXIS	CompensationDirection;				//非线性误差各轴补偿方向	0-neg  1-pos
	u16	ReferenceFrameMode;				//坐标系模型
	u16	GearDownRate;	 					//减速箱减速比
	s32	SpindleOneRing_EncoderRealDegree;	//主轴一圈编码器实际旋转角度;最小输入单位
}SYSTEM;	//系统参数结构组

typedef struct
{
	u8	S001;	//伺服驱动器型号:0-关闭此轴1-脉冲控制通用型号2-VT型号3-SGDV型号
	u8	S003;	//切换电机方向

	u32	S037;	//PG分频比(脉冲单位) [Pn212]
	u32	S038;	//电子齿轮比(分子) [Pn20E]
	u32	S039;	//电子齿轮比(分母) [Pn210]	
	u32	S106;	//S106 编码器线数
	u32	S107;	//S107 电机一转对应直线距离或旋转角度unit:nm or nd
	u32	S108;	//S108 减速比分子
	u32	S109;	//S109 减速比分母
	
	double		PWM_PeriodRegister;	// PWM 脉冲发生器周期  CH0906

   	volatile u16 	*PWM_Port;			//PWM 32BITS address
	
	volatile u16	*LPM_CounterPort;	//LPM counter 16bits address 
	u16 			LPM_CounterRegister;			// LPM 输出计数值

	double		Resolution;					// 分辨率UNIT: 最小输入单位/pulse 	
	double 		AxisOutUnitEQU;				//UNIT: pulse/最小输出单位 	

}SERVO;

typedef struct
{
UINT16AXIS		EncoderError;				// 轴光栅尺报警   1--报警

	u16 		NCCodeBreak;				//ARM发送G代码不连续	
	u16 		RAMCodeCheckError;			//运行缓冲区G代码校验报警
	u16 		InterpolationOver;			//插补量超5mm报警
	u16 		TrackRunOutError;			//轨迹偏离报警
	u16 		HaveGetErrorDataSign;		//已截取错误数据标志, when ARM ->RET
	u16 		ORTError;					// 定位完成后角度偏移标志CH0604
 	u32 		RealRunCount;				//已截取错误数据运行条数
	
	u16 		AAT_OverTravel;			////自动对刀功能报警 超行程报警
	u16 		AAT_OverSpeedSign;		// //自动对刀信号有效时超速报警 >300mm/min  1-报警
	
	u16 		A4RunLockError;					// A4 轴运行时锁紧报警
	u16 		A4StopUnlockError;				// A4 轴停止时松开报警
	
	u16 		MainErrorSign;				//总错误标志

	UINT16AXIS ServoSpindleAlarmCode;		//SERVO, Spindle报警码
	UINT8AXIS  ServoSpindleSystemParaDifferentNum;	//SERVO,Spindle系统参数不一致序号
	UINT16AXIS ServoAlarm;							//伺服报警		1:报警有效
}CERROR;					//报警结构组

typedef struct
{
	u16	XYZ_Over;               			// 1--完成当前G代码XYZ轴运行     
	
	u16	PrecalCode;					// 1--已预先计算G代码 
	u16 	GetPositionSign;				//--需获得稳定反馈坐标值标志
	u16	NewAreaSign;				//新区域标志
       u16  DelayCnt;
       u16  AllOver;                                   //  1  正在运行   0  包括闭环已经运行完
       u16  DelayAllOver;                         //  停下来已经过了稳定时间
	u16  ClosedLoopPosition;               //0   不需要    1    需要
	u16  CloseLoopStart;                      //0   还没开始    1  开始一次定位过程,考虑操作系统有可能从中间调用代码
	u16  RunPartOne;                            //0    第一段还没走             1  已经走完第一段
	u16  RunPartTwo;                            //0    第二段还没开始走   1  已经走完第二段
	//单段功能
	u16 	SingleModeSign; 				// 0:单段OFF;    1:单段ON; INI=0
	u16 	NeedRunSingleSign;  			// 1:单条运行标志 INI=0
	u16 	SingleRunOver;  				// 1:完成单条运行标志 INI=0
	
	UINT16AXIS	NeedBack;			//0:  1:positive compensation 2:negtive compensation 

	//CH0601  断点处理功能
	u16	A4_RunSign;					//代表A4 运行标志

	double    	F;						//G代码设定进给速度  (mm/s)
	double   	FG0;					//G0代码设定进给速度 (mm/s)
	u16 	GGroup02;					//平面组群选择 G17(defaut) G18 G19
	u16 	GGroup15;					//准停模态选择  G61 G64(defaut)
	u16  	ScaleSign;				//比例缩放标志。1:有效。0:无效。
	INT40AXIS	ScaleCenter;		 	//比例缩放圆心点 .单位：线性轴最小输入单位
	FLOAT64AXIS	       ScaleCoefficient;		//比例缩放系数。一般情况下为1。
	u32 	RealSendCount;				//ARM实际发送分解代码位置指针
	u32 	RealRunCount;				//DSP实际运行分解代码位置指针
	u16	Waitsign;					//单段模式下等侍单条结束标志发送回ARM
	u32	LastRealSendCount;			//打入公共区域时及单段时使用
	u16	LastNCCodeSign;				// 目前执行G 代码为最后一条,用于解决停顿问题
	s32	Information32[3];				// SPC代码32位信息
	u32	EndCodeCount;				//速度为0的代码条
	u32	VeVmCalCount;				//上次计算过Ve,Vm的代码条	
}NC_RUN_SIGN;

typedef struct
{
	u16			SearchRefSign;		// 要求搜索参考点标志
	
	u16		  	RefStep;				//参考点搜索步骤
	u16         	RefStepA4;
	UINT16AXIS	NeedFindAxisSign;	// 需要搜索轴的标志
	UINT16AXIS	FindRefSign;		       // 已找到某轴参考点标志

       double   FeedRateX;
	double   FeedRateY;
	double   FeedRateZ;

	u16			SearchRefSignX:1;		// 要求搜索X轴参考点标志
	u16			SearchRefSignY:1;		// 要求搜索Y轴参考点标志
	u16			SearchRefSignZ:1;		// 要求搜索Z轴参考点标志
	u16			SearchRefSignA:1;		// 要求搜索A轴参考点标志
	u8                  PosX:1;            // 表示是否撞到限位          
	u8                  NegX:1;            // 表示是否撞到限位    
	u8                  PosY:1;            // 表示是否撞到限位    
	u8                  NegY:1;            // 表示是否撞到限位    
	u8                  PosZ:1;            // 表示是否撞到限位    
	u8                  NegZ:1;            // 表示是否撞到限位    
}REFERENCE;


typedef struct
{
	u16	LockSign;					// 要求锁紧A4 轴标志
	u16	LockGetStartTimeSign;		// 获得锁紧反馈有效后起始时间标志	
	u16	RunLockCounter;				// A4 轴运行时锁紧有效计数器
	u16	LockCompleteSign;			// 锁紧A4 轴完成标志
	u16	LockCompleteCounter;		// 锁紧A4 轴完成记数器
	u16	UnlockSign;					// 要求松开A4 轴标志
	u16	UnlockGetStartTimeSign;		// 获得松开反馈有效后起始时间标志	
	u16	StopUnlockCounter;			//A4 轴停止时 松开有效计数器
	u16	UnlockCompleteSign;			// 松开A4 轴完成标志
	u16	UnlockCompleteCounter;		// 松开A4 轴完成记数器
	u16	SampleLockSign;				//采样A4 轴反馈锁紧有效标志
}A4AXIS;



//插补输出缓冲区  CH0902
typedef struct
{
	s16       X_GapSign;                  //     平摊间隙标志位
	s16       Y_GapSign;
	s16       Z_GapSign;
	s16       GapSign;
	INT40AXIS	DeltaPulse;				//缓冲区:  (单位: 插补段输出指令单位)
	INT40AXIS	AverageValue;			//平摊值
	INT40AXIS	MACHPosition;			//缓冲区:  (单位: 插补位置输出指令单位)
	u16 X_PWM_PeriodRegister;		// PWM 脉冲发生器周期  ch by bill
	u16 Y_PWM_PeriodRegister;			
	u16 Z_PWM_PeriodRegister;			
	u16 A_PWM_PeriodRegister;			
	u16 B_PWM_PeriodRegister;			
	u16 U_PWM_PeriodRegister;			
	u16 V_PWM_PeriodRegister;			
	u16 XSIGN ;                       // x轴运动方向
	u16 YSIGN ;                       // y轴运动方向
	u16 ZSIGN ;                       // z轴运动方向
	u16 ASIGN ;                       // a轴运动方向
	u16 BSIGN ;                       // b轴运动方向
	u16 USIGN ;                       //u轴运动方向
	u16 VSIGN ;                       // v轴运动方向
	double VNowOut;			// 暂存当前实际输出运行速度. (mm/s)
	UINT16AXIS MoveSign;
}INTERPOLATION_BUFFER;



typedef struct
{
    UINT40AXIS    PulseCount;
    FLOAT64AXIS  ScaleResetVal;
    FLOAT64AXIS  FollowErr;      // 最大跟随误差。单位。mm
    UINT40AXIS    PulseSend[100];
    VECTOR          Scale[100];
    u32                 PulsePtr;
}MONITORCON;

extern  MONITORCON  MonitorCon;


#endif  // end of COMMON_H definition


