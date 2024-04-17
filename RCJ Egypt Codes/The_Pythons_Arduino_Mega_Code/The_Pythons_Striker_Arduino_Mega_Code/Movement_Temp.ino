void MoveMotor(int Motor, int Speed)
{
  if (Speed > 100)
    Speed = 100;

  else if (Speed < -100)
    Speed = -100;
  Speed2 = Speed;
  Speed = abs(Speed);
  Speed = map(Speed , 0 , 100 , 0 , 254);
  //Serial.println(Speed);
  if (Motor == 1)
  {
    if (Speed2 < 0)
    {
      analogWrite(Down_Left_Direction, 0);
    }
    else
    {
      analogWrite(Down_Left_Direction, 255);
    }
    analogWrite(Down_Left_PWM, Speed);
  }
  else if (Motor == 2)
  {
    if (Speed2 < 0)
    {
      analogWrite(Down_Right_Direction, 255);
    }
    else
    {
      analogWrite(Down_Right_Direction, 0);
    }
    analogWrite(Down_Right_PWM, Speed);
  }
  else if (Motor == 3)
  {
    if (Speed2 < 0)
    {
      analogWrite(Upper_Left_Direction, 0);
    }
    else
    {
      analogWrite(Upper_Left_Direction, 255);
    }
    analogWrite(Upper_Left_PWM, Speed);
  }
  else if (Motor == 4)
  {
    if (Speed2 < 0)
    {
      analogWrite(Upper_Right_Direction, 255);
    }
    else
    {
      analogWrite(Upper_Right_Direction, 0);
    }
    analogWrite(Upper_Right_PWM, Speed);
  }
}

// Striker (new motors)
void motioneq()
{
  temp = forward - side;
  speeda = temp + turn;
  speedc = temp - turn;
  temp = side + forward;
  speedb = temp + turn;
  speedd = temp - turn;
  MoveMotor(2, -speedd);
  MoveMotor(4, -speedc);
  MoveMotor(3, -speedb);
  MoveMotor(1, -speeda);
  //Serial.println("motq");
}

//// Keeper (old motors)
//void motioneq()
//{
//  temp = forward - side;
//  speeda = temp + turn;
//  speedc = temp - turn;
//  temp = side + forward;
//  speedb = temp + turn;
//  speedd = temp - turn;
//  MoveMotor(2, -speedd);
//  MoveMotor(4, -speedc);
//  MoveMotor(3, speedb);
//  MoveMotor(1, speeda);
//  //Serial.println("motq");
//}

void Line_motion()
{
  temp = forward - side;
  speeda = temp - turn;
  speedc = temp + turn;
  temp = side + forward;
  speedb = temp - turn;
  speedd = temp + turn;
  MoveMotor(2, -speedd);
  MoveMotor(4, -speedc);
  MoveMotor(3, -speedb);
  MoveMotor(1, -speeda);
  //Serial.println("lm");
}

void Stop_All()
{
  MoveMotor(1, 0);
  MoveMotor(2, 0);
  MoveMotor(3, 0);
  MoveMotor(4, 0);
  flag = 0;
}
