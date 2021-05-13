// Copyright 2021 the Drakhtar authors. All rights reserved. MIT license.

#pragma once

#include "Format/Numbers/Systems/ISystem.h"

class Latin : public ISystem {
 public:
  Latin() : ISystem('0', '1', '2', '3', '4', '5', '6', '7', '8', '9') {}
};
