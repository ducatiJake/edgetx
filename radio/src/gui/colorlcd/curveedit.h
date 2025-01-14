/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   opentx - https://github.com/opentx/opentx
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#pragma once

#include "form.h"
#include "curve.h"

class CurveEdit;

class CurveDataEdit : public FormGroup
{
  friend class CurveEdit;

  public:
    CurveDataEdit(Window * parent, const rect_t & rect, uint8_t index, CurveEdit * curveEdit);

    void paint(BitmapBuffer * dc) override;

    void update();

  protected:
    uint8_t index;
    CurveEdit * curveEdit;
};

class CurveEdit: public FormField
{
  friend class CurveDataEdit;

  public:
    CurveEdit(Window * parent, const rect_t & rect, uint8_t index);
    static void SetCurrentSource(uint32_t source);

    void deleteLater(bool detach = true, bool trash = true) override
    {
      if (_deleted)
        return;

      preview.deleteLater(true, false);

      FormField::deleteLater(detach, trash);
    }

    void updatePreview();

    void onEvent(event_t event) override;
    void checkEvents(void) override;

    // #if defined(HARDWARE_TOUCH)
    //     bool onTouchEnd(coord_t x, coord_t y) override;
    //     void onFocusLost() override;
    // #endif

   protected:
    Curve preview;
    uint8_t index;
    uint8_t current;
    static mixsrc_t currentSource;
    static bool lockSource;
    void next();
    void previous();
    void up();
    void down();
    void right();
    void left();
    bool isCustomCurve() const;
};
