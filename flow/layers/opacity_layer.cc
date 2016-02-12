// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flow/layers/opacity_layer.h"

#include "flow/quads/ephemeral_quad.h"

namespace flow {

OpacityLayer::OpacityLayer() {
}

OpacityLayer::~OpacityLayer() {
}

void OpacityLayer::Preroll(PrerollContext* context, const SkMatrix& matrix) {
  ContainerLayer::Preroll(context, matrix);
  set_paint_bounds(context->child_paint_bounds);
}

void OpacityLayer::Paint(PaintContext::ScopedFrame& frame) {
  SkPaint paint;
  paint.setColor(SkColorSetARGB(alpha_, 0, 0, 0));
  paint.setXfermodeMode(SkXfermode::kSrcOver_Mode);

  SkCanvas& canvas = frame.canvas();
  SkAutoCanvasRestore save(&canvas, false);
  canvas.saveLayer(&paint_bounds(), &paint);
  PaintChildren(frame);
}

void OpacityLayer::CollectQuads(QuadCollector& collector) {
  QuadCollector children;
  ContainerLayer::CollectQuads(children);

  std::unique_ptr<EphemeralQuad> quad(new EphemeralQuad());
  quad->set_children(std::move(children.quads));
  collector.quads.push_back(std::move(quad));
}

}  // namespace flow
