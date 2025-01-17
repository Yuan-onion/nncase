/* Copyright 2019 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <cassert>
#include <ir/graph.h>
#include <scheduler/scheduler.h>
#include <unordered_map>

namespace nncase
{
namespace ir
{
    class quantizer
    {
    public:
        template<class TIt>
        value_range<float> get_range(TIt begin, TIt end)
        {
            auto minmax = std::minmax_element(begin, end);
            return { *minmax.first, *minmax.second };
        }

        void record(ir::output_connector &connector, value_range<float> range);
        void record(ir::output_connector &connector, xtl::span<const float> data);
        value_range<float> get(ir::output_connector &connector) const;
        quant_param_t get_quant_param(value_range<float> range, int32_t bits) const;
        fixed_mul get_fixed_mul(float value, int32_t max_bits, uint8_t max_shift, bool is_signed) const;

    private:
        std::unordered_map<ir::output_connector *, value_range<float>> quant_ranges_;
    };
}
}
