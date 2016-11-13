#pragma hdrstop
#include "uFunction.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
bool JoyStick(TJoy *Joy)
{
  JOYINFOEX j;

  j.dwSize = sizeof(JOYINFOEX);
  j.dwFlags = JOY_RETURNALL;

  if (joyGetPosEx(JOYSTICKID1, &j) == JOYERR_NOERROR) {
    Joy->A = (j.dwButtons & JOY_BUTTON1) > 0;
    Joy->B = (j.dwButtons & JOY_BUTTON2) > 0;
    Joy->X = (j.dwButtons & JOY_BUTTON3) > 0;
    Joy->Y = (j.dwButtons & JOY_BUTTON4) > 0;

    Joy->LB = (j.dwButtons & JOY_BUTTON5) > 0;
    Joy->RB = (j.dwButtons & JOY_BUTTON6) > 0;

    Joy->Back  = (j.dwButtons & JOY_BUTTON7) > 0;
    Joy->Start = (j.dwButtons & JOY_BUTTON8) > 0;

    Joy->Pad.Right = j.dwPOV == JOY_POVRIGHT;
    Joy->Pad.Down  = j.dwPOV == JOY_POVBACKWARD;
    Joy->Pad.Left  = j.dwPOV == JOY_POVLEFT;
    Joy->Pad.Up    = j.dwPOV == JOY_POVFORWARD;

    Joy->LT = j.dwZpos > 0x7FFF;
    Joy->RT = j.dwZpos < 0x7FFF;

    Joy->Analogic[0].Right = j.dwXpos > 0x7FFF + 0x5FFF;
    Joy->Analogic[0].Down  = j.dwYpos > 0x7FFF + 0x5FFF;
    Joy->Analogic[0].Left  = j.dwXpos < 0x7FFF - 0x5FFF;
    Joy->Analogic[0].Up    = j.dwYpos < 0x7FFF - 0x5FFF;

    Joy->Analogic[1].Right = j.dwUpos > 0x7FFF + 0x5FFF;
    Joy->Analogic[1].Down  = j.dwRpos > 0x7FFF + 0x5FFF;
    Joy->Analogic[1].Left  = j.dwUpos < 0x7FFF - 0x5FFF;
    Joy->Analogic[1].Up    = j.dwRpos < 0x7FFF - 0x5FFF;

    return true;
  }
  return false;
}
//---------------------------------------------------------------------------
TBitmap *Png2Bmp(String filename)
{
  TPngImage *png = new TPngImage();
  png->LoadFromFile(filename);
  TBitmap *bmp = new TBitmap();
  bmp->Assign(png);
  delete png;
  return bmp;
}
//---------------------------------------------------------------------------
TStringList *explode(String Text, String Separator)
{
  TStringList *s = new TStringList();
  int p = pos(Separator, Text);
  while (p > 0) {
    s->Add(Text.SubString(1, p - 1));
    Text.Delete(1, p + Separator.Length() - 1);
    p = pos(Separator, Text);
  }
  if (Text != "") {
    s->Add(Text);
  }
  return s;
}
