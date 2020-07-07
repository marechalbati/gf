/*
 * Gamedev Framework (gf)
 * Copyright (C) 2016-2019 Julien Bernard
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */
#version 100

precision mediump float;

varying vec4 v_color;
varying vec2 v_texCoords;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform float u_progress;

void main(void) {
  vec4 texel0 = texture2D(u_texture0, v_texCoords);
  vec4 texel1 = texture2D(u_texture1, v_texCoords);
  vec4 blackPix = vec4(0.0, 0.0, 0.0, 1.0);

  float progress0 = clamp(u_progress - 0.5, -0.5, 0.0) * -2.0;
  float progress1 = clamp(u_progress - 0.5, 0.0, 0.5) * 2.0;

  gl_FragColor = (mix(blackPix, texel0, progress0) + mix(blackPix, texel1, progress1)) * v_color;
}
