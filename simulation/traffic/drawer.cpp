#include <iostream>
#include <autogl.h>
#include <string>
#include <math.h>
#include <vector>
#include "car.h"
#include "node.h"
#include "link.h"
#include "signal.h"
#include "config.h"
#include "calculation.h"

using namespace std;

extern double PresentTime;
extern double Size;

extern vector<CAR> CAR;
extern vector<LINK> LINK;
extern vector<NODE> NODE;
extern vector<SIGNAL> SIGNAL;

double x;
double y;
double d=2.0;//車長
double w=1.0;//車幅


double GET_LEADING_CAR_ID(int CarID)
{
  int LeadingCarID=-1;
  double MinDistance=Infinity;


  for(int i=0;i<CarMax;i++)
    {
      if(CAR[i].CAR_USED() == 1 &&
	 CAR[CarID].LINK_ID() == CAR[i].LINK_ID())
	{
	  int LinkID = CAR[i].LINK_ID();
	  if(LINK[LinkID].DIRECTION_X()*(CAR[i].X()-CAR[CarID].X())>0 ||
	     LINK[LinkID].DIRECTION_Y()*(CAR[i].Y()-CAR[CarID].Y())>0)
	    {
	      if(MinDistance>length(CAR[i].X(),CAR[i].Y(),
				    CAR[CarID].X(),CAR[CarID].Y())-5);
	      {
		MinDistance=length(CAR[i].X(),CAR[i].Y(),
				   CAR[CarID].X(),CAR[CarID].Y())-5;
		LeadingCarID=i;
	      }
	    }
	}
      else if(CAR[i].CAR_USED() == 1 &&
	      CAR[CarID].NEXT_LINK_ID() == CAR[i].LINK_ID())
	{
	  int LinkID = CAR[CarID].LINK_ID();
	  double l;
	  l=length(CAR[i].X(),CAR[i].Y(),
		   LINK[LinkID].END_X(),LINK[LinkID].END_Y())
	    +length(CAR[CarID].X(),CAR[CarID].Y(),
		    LINK[LinkID].END_X(),LINK[LinkID].END_Y())-5;


	  if(MinDistance>l)
	    {
	      MinDistance=l;
	      LeadingCarID=i;
	    }

	}
    }
  return LeadingCarID;
}

void drawRoad()
{
  //DRAW NODE
    for(int i=0;i<NodeMax;i++)
    {
      if(NODE[i].USED()==1)
	{
	  AutoGL_SetColor(1,1,1);
	  AutoGL_DrawCircle3D(NODE[i].X(),NODE[i].Y(),0.2,0,0,1,0.5,10);
	}
    }

  //DRAW LINK
    for(int i=0;i<LinkMax;i++)
    {
      if(LINK[i].USED()==1)
	{
	  AutoGL_SetColor(1,1,1);
	        AutoGL_DrawLine(LINK[i].START_X(),LINK[i].START_Y(),0.2,
				LINK[i].END_X(),LINK[i].END_Y(),0.2);
	}
    }

  for(int i=0;i<LinkMax;i++)
    {
      if(LINK[i].USED()==0)
	continue;

      double RoadWidth=4;
      double SideWidth=1.5;

      double x1=LINK[i].START_X()+LINK[i].DIRECTION_Y()*RoadWidth;
      double x2=LINK[i].START_X()-LINK[i].DIRECTION_Y()*RoadWidth;
      double x3=LINK[i].END_X()-LINK[i].DIRECTION_Y()*RoadWidth;
      double x4=LINK[i].END_X()+LINK[i].DIRECTION_Y()*RoadWidth;
      double y1=LINK[i].START_Y()+LINK[i].DIRECTION_X()*RoadWidth;
      double y2=LINK[i].START_Y()-LINK[i].DIRECTION_X()*RoadWidth;
      double y3=LINK[i].END_Y()-LINK[i].DIRECTION_X()*RoadWidth;
      double y4=LINK[i].END_Y()+LINK[i].DIRECTION_X()*RoadWidth;

      AutoGL_SetColor(0.8, 0.8, 0.8);
      AutoGL_DrawQuadrangle(x1,y1,0.1,x2,y2,0.1,
			    x3,y3,0.1,x4,y4,0.1);

      RoadWidth+=SideWidth;;
      x1=LINK[i].START_X()+LINK[i].DIRECTION_Y()*RoadWidth;
      x2=LINK[i].START_X()-LINK[i].DIRECTION_Y()*RoadWidth;
      x3=LINK[i].END_X()-LINK[i].DIRECTION_Y()*RoadWidth;
      x4=LINK[i].END_X()+LINK[i].DIRECTION_Y()*RoadWidth;
      y1=LINK[i].START_Y()+LINK[i].DIRECTION_X()*RoadWidth;
      y2=LINK[i].START_Y()-LINK[i].DIRECTION_X()*RoadWidth;
      y3=LINK[i].END_Y()-LINK[i].DIRECTION_X()*RoadWidth;
      y4=LINK[i].END_Y()+LINK[i].DIRECTION_X()*RoadWidth;

      AutoGL_SetColor(0.3, 0.3, 0.3);
      AutoGL_DrawQuadrangle(x1,y1,0,x2,y2,0,
			    x3,y3,0,x4,y4,0);

    }
}

void drawSignal()
{

  double x=0;
  double y=8;
  double dx=5;
  double dy=2;

  for(int i=0;i<2;i++)
    {
      AutoGL_SetColor(0.7, 0.7, 0.7);
      AutoGL_DrawQuadrangle ((x+dx),(y*pow(-1,i)+dy), 0.5,
			     (x+dx),(y*pow(-1,i)-dy), 0.5,
			     (x-dx),(y*pow(-1,i)-dy), 0.5,
			     (x-dx),(y*pow(-1,i)+dy), 0.5);
    }
  for(int i=0;i<2;i++)
    {
      AutoGL_SetColor(0.7, 0.7, 0.7);
      AutoGL_DrawQuadrangle ((y*pow(-1,i)+dy),(x+dx), 0.5,
			     (y*pow(-1,i)-dy),(x+dx), 0.5,
			     (y*pow(-1,i)-dy),(x-dx), 0.5,
			     (y*pow(-1,i)+dy),(x-dx), 0.5);
    }

  for(int i=0;i<2;i++)
    {
      SIGNAL[i].CHANGE_SIGNAL(PresentTime);
    }

   switch (SIGNAL[0].SIGNAL_COLOR())
    {
    case BlueSignal :
      AutoGL_SetColor(0, 0, 1);
      AutoGL_DrawCircle3D(y, (x-3), 0.6, 0, 0, 1, 1, 10);
      AutoGL_DrawCircle3D(y*(-1), (x-3)*(-1), 0.6, 0, 0, 1, 1, 10);
      break;
    case YellowSignal :
      AutoGL_SetColor(1, 1, 0);
      AutoGL_DrawCircle3D(y, x, 0.6, 0, 0, 1, 1, 10);
      AutoGL_DrawCircle3D(y*(-1), x*(-1), 0.6, 0, 0, 1, 1, 10);
      break;
    case RedSignal :
      AutoGL_SetColor(1, 0, 0);
      AutoGL_DrawCircle3D(y, (x+3), 0.6, 0, 0, 1, 1, 10);
      AutoGL_DrawCircle3D(y*(-1), (x+3)*(-1), 0.6, 0, 0, 1, 1, 10);
      break;
    }

     switch (SIGNAL[1].SIGNAL_COLOR())
    {
    case BlueSignal :
      AutoGL_SetColor(0, 0, 1);
      AutoGL_DrawCircle3D((x+3), y, 0.6, 0, 0, 1, 1, 10);
      AutoGL_DrawCircle3D((x+3)*(-1),y*(-1), 0.6, 0, 0, 1, 1, 10);
      break;
    case YellowSignal :
      AutoGL_SetColor(1, 1, 0);
      AutoGL_DrawCircle3D(x, y, 0.6, 0, 0, 1, 1, 10);
      AutoGL_DrawCircle3D(x*(-1), y*(-1), 0.6, 0, 0, 1, 1, 10);
      break;
    case RedSignal :
      AutoGL_SetColor(1, 0, 0);
      AutoGL_DrawCircle3D((x-3), y, 0.6, 0, 0, 1, 1, 10);
      AutoGL_DrawCircle3D((x-3)*(-1), y*(-1), 0.6, 0, 0, 1, 1, 10);
      break;
    }

}



void drawCar()
{

  for(int i=0;i<CarMax;i++)
    {
      if(CAR[i].CAR_USED()==1)
	{
	  double Acceleration_LeadingCar;
	  double Acceleration_Signal;
	  double Acceleration_Turn;
	  double Acceleration_RightTurn;

	  double Acceleration;

	  /* 先行車追従加速度 */
	  /*------------------------------------------------------------------------*/
	  double CarDistance=Infinity;
	  double deltaV=0;
	  int j=GET_LEADING_CAR_ID(i);

	  if(CAR[j].CAR_USED()==1 && CAR[i].LINK_ID()==CAR[j].LINK_ID())
	    {
	      CarDistance=length(CAR[i].X(),CAR[i].Y(),
				 CAR[j].X(),CAR[j].Y())-5;
	      deltaV=CAR[i].V()-CAR[j].V();
	    }
	  else if(CAR[j].CAR_USED()==1 && CAR[i].LINK_ID()!=CAR[j].LINK_ID())
	    {
	      int LinkID=CAR[i].LINK_ID();
	      CarDistance=length(CAR[i].X(),CAR[i].Y(),
				 LINK[LinkID].END_X(),LINK[LinkID].END_Y())
		+length(CAR[j].X(),CAR[j].Y(),
			LINK[LinkID].END_X(),LINK[LinkID].END_Y())-5;
	      deltaV=CAR[i].V()-CAR[j].V();
	    }

	  Acceleration_LeadingCar=CAR[i].ACCELERATE(CarDistance,deltaV);

/* 信号用加速度 */
/*------------------------------------------------------------------------*/
	  if(CAR[i].LINK_ID()==0||CAR[i].LINK_ID()==6)
	    {
	      Acceleration_Signal=SIGNAL[0].ACCELERATION(i);
	    }
	  else if(CAR[i].LINK_ID()==12||CAR[i].LINK_ID()==18)
	    {
	      Acceleration_Signal=SIGNAL[1].ACCELERATION(i);
	    }
	  else
	    {
	      Acceleration_Signal=Infinity;
	    }
/* 右左折時減速用加速度 */
/*------------------------------------------------------------------------*/

	  double TurningDistance=Infinity;

	  if(CAR[i].DESTINATION()!=GoStraight && (int)CAR[i].LINK_ID()%6==0)
	    {
	      TurningDistance=length(CAR[i].X(),CAR[i].Y(),
				     LINK[(int)CAR[i].LINK_ID()].END_X(),
				     LINK[(int)CAR[i].LINK_ID()].END_Y())+100;
	    }

	  Acceleration_Turn=CAR[i].ACCELERATE(TurningDistance,CAR[i].V());

/* 右折時対向車用加速度 */
/*------------------------------------------------------------------------*/

	  double TurnRightDistance=Infinity;
	  int OncomingCarID=-1;
	  int Decision=0;

	  //LINK 0
	  if(CAR[i].DESTINATION()==TurnRight && CAR[i].LINK_ID()==4)
	    {
	      double MinDistance=Infinity;

	      for(int k=0;k<CarMax;k++)
		{
		  if(CAR[k].CAR_USED()==1 && CAR[k].DESTINATION()!=TurnRight && CAR[k].X()>4 &&
		     (CAR[k].LINK_ID()==6 || CAR[k].LINK_ID()==7 ||CAR[k].LINK_ID()==9))
		    {

		      if(MinDistance>length(CAR[k].X(),CAR[k].Y(),4,-4))
			{
			  MinDistance=length(CAR[k].X(),CAR[k].Y(),4,-4);
			  OncomingCarID=k;
			}

		    }
		}

	      //行くかどうか意思決定

	      if(CAR[OncomingCarID].X()>4 &&
		 fabs(CAR[i].X())<30 && fabs(CAR[i].Y())<30)
		{
		  if(CAR[OncomingCarID].SIGNAL_DECISION(-1)==0||
		     CAR[OncomingCarID].V()<=1)
		    {
		      Decision=1;
		    }
		  else if(MinDistance/CAR[OncomingCarID].V()>6)
		    {
		      Decision=1;
		    }
		  else
		    {
		      Decision=-1;
		    }
		}

	      //判断
	      if(CAR[i].RIGHT_TURN_DECISION(Decision)==-1)
		{
		  TurnRightDistance=length(CAR[i].X(),CAR[i].Y(),-3,-1);
		}
	    }


	  //LINK 6
	  if(CAR[i].DESTINATION()==TurnRight && CAR[i].LINK_ID()==10)
	    {
	      double MinDistance=Infinity;

	      for(int k=0;k<CarMax;k++)
		{
		  if(CAR[k].CAR_USED()==1 && CAR[k].DESTINATION()!=TurnRight && CAR[k].X()<-4 &&
		     (CAR[k].LINK_ID()==0 || CAR[k].LINK_ID()==1 ||CAR[k].LINK_ID()==3))
		    {

		      if(MinDistance>length(CAR[k].X(),CAR[k].Y(),-4,4))
			{
			  MinDistance=length(CAR[k].X(),CAR[k].Y(),-4,4);
			  OncomingCarID=k;
			}

		    }
		}

	      //行くかどうか意思決定
	      if(CAR[OncomingCarID].X()<-4)
		{
		  if(fabs(CAR[i].X())<30 && fabs(CAR[i].Y())<30 &&
		     MinDistance/CAR[OncomingCarID].V()>6)
		    {
		      Decision=1;
		    }
		  else
		    {
		      Decision=-1;
		    }
		}
	      else
		{
		  Decision=1;
		}
	      if(CAR[OncomingCarID].SIGNAL_DECISION(-1)==0||
		 CAR[OncomingCarID].V()<=1)
		{
		  Decision=1;
		}

	      //判断

	      if(CAR[i].RIGHT_TURN_DECISION(Decision)==-1)
		{
		  TurnRightDistance=length(CAR[i].X(),CAR[i].Y(),3,1);
		}
	    }

	  //LINK 12
	  if(CAR[i].DESTINATION()==TurnRight && CAR[i].LINK_ID()==16)
	    {
	      double MinDistance=Infinity;

	      for(int k=0;k<CarMax;k++)
		{
		  if(CAR[k].CAR_USED()==1 && CAR[k].DESTINATION()!=TurnRight && CAR[k].Y()>4 &&
		     (CAR[k].LINK_ID()==18 || CAR[k].LINK_ID()==19 ||CAR[k].LINK_ID()==20))
		    {

		      if(MinDistance>length(CAR[k].X(),CAR[k].Y(),4,4))
			{
			  MinDistance=length(CAR[k].X(),CAR[k].Y(),4,4);
			  OncomingCarID=k;
			}

		    }
		}

	      //行くかどうか意思決定

	      if(CAR[OncomingCarID].Y()>4 &&
		 fabs(CAR[i].X())<30 && fabs(CAR[i].Y())<30)
		{
		  if(CAR[OncomingCarID].SIGNAL_DECISION(-1)==0||
		     CAR[OncomingCarID].V()<=1)
		    {
		      Decision=1;
		    }
		  else if(MinDistance/CAR[OncomingCarID].V()>6)
		    {
		      Decision=1;
		    }
		  else
		    {
		      Decision=-1;
		    }
		}

	      //判断
	      if(CAR[i].RIGHT_TURN_DECISION(Decision)==-1)
		{
		  TurnRightDistance=length(CAR[i].X(),CAR[i].Y(),1,-3);
		}
	    }


	  //LINK 18
	  if(CAR[i].DESTINATION()==TurnRight && CAR[i].LINK_ID()==22)
	      {
	    	double MinDistance=Infinity;

	    	for(int k=0;k<CarMax;k++)
	    	  {
	    	    if(CAR[k].CAR_USED()==1 && CAR[k].DESTINATION()!=TurnRight && CAR[k].Y()<-4 &&
	    	       (CAR[k].LINK_ID()==12 || CAR[k].LINK_ID()==13 ||CAR[k].LINK_ID()==14))
	    	      {

	    		if(MinDistance>length(CAR[k].X(),CAR[k].Y(),-4,-4))
	    		  {
	    		    MinDistance=length(CAR[k].X(),CAR[k].Y(),-4,-4);
	    		    OncomingCarID=k;
	    		  }

	    	      }
	    	  }

	    	//行くかどうか意思決定
	    	if(CAR[OncomingCarID].Y()<-4)
	    	  {
	    	    if(fabs(CAR[i].X())<30 && fabs(CAR[i].Y())<30 &&
		       MinDistance/CAR[OncomingCarID].V()>6)
	    	      {
	    		Decision=1;
	    	      }
	    	    else
	    	      {
	    		Decision=-1;
	    	      }
	    	  }
	    	else
	    	  {
	    	    Decision=1;
	    	  }
	    	if(CAR[OncomingCarID].SIGNAL_DECISION(-1)==0||
	    	   CAR[OncomingCarID].V()<=1)
	    	  {
	    	    Decision=1;
	    	  }

	    	//判断

	    	if(CAR[i].RIGHT_TURN_DECISION(Decision)==-1)
	    	  {
	    	    TurnRightDistance=length(CAR[i].X(),CAR[i].Y(),-1,3);
	    	  }
	      }

	    Acceleration_RightTurn=CAR[i].ACCELERATE(TurnRightDistance,CAR[i].V());

/* 最小加速度の決定 */
/*------------------------------------------------------------------------*/

	    Acceleration=min(min(Acceleration_LeadingCar,Acceleration_Signal),
			     min(Acceleration_Turn,Acceleration_RightTurn));


	    CAR[i].GET_ACCELERATION(Acceleration);

	  }
    }

/* 車の移動と描写 */
/*------------------------------------------------------------------------*/
  for(int i=0;i<CarMax;i++)
    {
      if(CAR[i].CAR_USED()==1)
	  {
      	    int LinkID=CAR[i].LINK_ID();

	    CAR[i].MOVE();

	    x=CAR[i].X();
	    y=CAR[i].Y();

	    double cos=LINK[LinkID].DIRECTION_X();
	    double sin=LINK[LinkID].DIRECTION_Y();

	    switch ((int)CAR[i].DESTINATION())
	      {
	      case GoStraight :
	    AutoGL_SetColor(1, 0, 0);
	    break;
	      case TurnRight :
	    AutoGL_SetColor(1, 0.6, 0);
	    break;
	      case TurnLeft :
	    AutoGL_SetColor(1, 0.3, 0);
	    break;
	      }

	    AutoGL_DrawQuadrangle (x+d*cos-w*sin,y+d*sin+w*cos, 1,
				   x-d*cos-w*sin,y-d*sin+w*cos, 1,
				   x-d*cos+w*sin,y-d*sin-w*cos, 1,
				   x+d*cos+w*sin,y+d*sin-w*cos, 1);
	  }
    }
}
