// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef VFX_SHADOWS_SHADOW_RENDERER_H_
#define VFX_SHADOWS_SHADOW_RENDERER_H_

#include <memory>

#include "ui/gfx/geometry/size.h"
#include "vfx/gl/array_buffer.h"
#include "vfx/gl/color_program.h"
#include "vfx/gl/element_array_buffer.h"
#include "vfx/gl/frame_buffer.h"
#include "vfx/shadows/shadow_scene.h"

namespace vfx {

class ShadowRenderer {
 public:
  explicit ShadowRenderer(ShadowScene scene);
  ~ShadowRenderer();

  void PrepareToDraw();
  void Draw(const gfx::Size size);

 private:
  ShadowScene scene_;

  std::unique_ptr<ColorProgram> color_program_;
  ElementArrayBuffer<ShadowScene::Vertex> geometry_;
  ArrayBuffer<Point> shadow_;
  ElementArrayBuffer<ShadowScene::Vertex> shadow_mask_;

  FrameBuffer frame_buffer_;
};

}  // namespace vfx

#endif  // VFX_SHADOWS_SHADOW_RENDERER_H_
