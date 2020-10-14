#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <QString>
#include <QDebug>
#include <QMap>

#include "../Common/configfilepath.h"
#include "../Data/data.h"

#include "statebase.h"
#include "States/stop.h"
#include "States/starting.h"
#include "States/traveling.h"
#include "States/stopping.h"
#include "States/stacking.h"
#include "States/stacking.h"

#include "States/manualcontrol.h"

class Behavior
{
public:
  Behavior();

	int init();
  int setThread(QThread *th);
  void main(Data *data);

private:
  Stop *stop;
  Starting *starting;
  Traveling *traveling;
  Stopping *stopping;
  //	Stacking *stacking;

	ManualControl *manualControl;

private:
  QMap<int, StateBase*> state;
};

#endif // BEHAVIOR_H
