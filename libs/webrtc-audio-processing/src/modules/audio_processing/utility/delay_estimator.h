/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

// Performs delay estimation on a block by block basis
// The return value is  0 - OK and -1 - Error, unless otherwise stated.

#ifndef WEBRTC_MODULES_AUDIO_PROCESSING_UTILITY_DELAY_ESTIMATOR_H_
#define WEBRTC_MODULES_AUDIO_PROCESSING_UTILITY_DELAY_ESTIMATOR_H_

#include "typedefs.h"

// Releases the memory allocated by WebRtc_CreateDelayEstimator(...)
// Input:
//      - handle        : Pointer to the delay estimation instance
//
int WebRtc_FreeDelayEstimator(void* handle);

// Allocates the memory needed by the delay estimation. The memory needs to be
// initialized separately using the WebRtc_InitDelayEstimator(...)
// function.
//
// Inputs:
//      - handle            : Instance that should be created
//      - spectrum_size     : Size of the spectrum used both in far end and
//                            near end. Used to allocate memory for spectrum
//                            specific buffers.
//      - history_size      : Size of the far end history used to estimate the
//                            delay from. Used to allocate memory for history
//                            specific buffers.
//      - enable_alignment  : With this mode set to 1, a far end history is
//                            created, so that the user can retrieve aligned
//                            far end spectra using
//                            WebRtc_AlignedFarend(...). Otherwise, only delay
//                            values are calculated.
//
// Output:
//      - handle            : Created instance
//
int WebRtc_CreateDelayEstimator(void** handle,
                                int spectrum_size,
                                int history_size,
                                int enable_alignment);

// Initializes the delay estimation instance created with
// WebRtc_CreateDelayEstimator(...)
// Input:
//      - handle        : Pointer to the delay estimation instance
//
// Output:
//      - handle        : Initialized instance
//
int WebRtc_InitDelayEstimator(void* handle);

// Estimates and returns the delay between the far end and near end blocks.
// Inputs:
//      - handle        : Pointer to the delay estimation instance
//      - far_spectrum  : Pointer to the far end spectrum data
//      - near_spectrum : Pointer to the near end spectrum data of the current
//                        block
//      - spectrum_size : The size of the data arrays (same for both far and
//                        near end)
//      - far_q         : The Q-domain of the far end data
//      - vad_value     : The VAD decision of the current block
//
// Output:
//      - handle        : Updated instance
//
// Return value:
//      - delay         :  >= 0 - Calculated delay value
//                        -1    - Error
//
int WebRtc_DelayEstimatorProcess(void* handle,
                                 uint16_t* far_spectrum,
                                 uint16_t* near_spectrum,
                                 int spectrum_size,
                                 int far_q,
                                 int vad_value);

// Returns a pointer to the far end spectrum aligned to current near end
// spectrum. The function WebRtc_DelayEstimatorProcess(...) should have been
// called before WebRtc_AlignedFarend(...). Otherwise, you get the pointer to
// the previous frame. The memory is only valid until the next call of
// WebRtc_DelayEstimatorProcess(...).
//
// Inputs:
//      - handle            : Pointer to the delay estimation instance
//      - far_spectrum_size : Size of far_spectrum allocated by the caller
//
// Output:
//      - far_q             : The Q-domain of the aligned far end spectrum
//
// Return value:
//      - far_spectrum      : Pointer to the aligned far end spectrum
//                            NULL - Error
//
const uint16_t* WebRtc_AlignedFarend(void* handle,
                                     int far_spectrum_size,
                                     int* far_q);

// Returns the last calculated delay updated by the function
// WebRtc_DelayEstimatorProcess(...)
//
// Input:
//      - handle        : Pointer to the delay estimation instance
//
// Return value:
//      - delay         :  >= 0 - Last calculated delay value
//                        -1    - Error
//
int WebRtc_last_delay(void* handle);

// Returns the history size used in the far end buffers to calculate the delay
// over.
//
// Input:
//      - handle        : Pointer to the delay estimation instance
//
// Return value:
//      - history_size  :  > 0  - Far end history size
//                        -1    - Error
//
int WebRtc_history_size(void* handle);

// Returns the fixed spectrum size used in the algorithm.
//
// Input:
//      - handle        : Pointer to the delay estimation instance
//
// Return value:
//      - spectrum_size :  > 0  - Spectrum size
//                        -1    - Error
//
int WebRtc_spectrum_size(void* handle);

// Returns 1 if the far end alignment is enabled and 0 otherwise.
//
// Input:
//      - handle        : Pointer to the delay estimation instance
//
// Return value:
//      - alignment_enabled : 1 - Enabled
//                            0 - Disabled
//                           -1 - Error
//
int WebRtc_is_alignment_enabled(void* handle);

#endif  // WEBRTC_MODULES_AUDIO_PROCESSING_UTILITY_DELAY_ESTIMATOR_H_
