#pragma once

#include "common.h"

class Bridge : public Shape {

public:
    Bridge();

//private:

    float m_data[8 * 240] = {
            -0.194764, 2.95172, -0.607465, -0.999966, 0.000421, 0.008261, 0.375, 0,
            -0.194722, 2.96538, -0.603051, -0.999966, 0.000421, 0.008261, 0.625, 0,
            -0.195222, 2.98516, -0.664616, -0.999966, 0.000421, 0.008261, 0.625, 0.25,
            -0.195264, 2.97149, -0.668992, -0.999966, 0.000421, 0.008261, 0.375, 0.25,
            -0.195264, 2.97149, -0.668992, -0.007398, 0.304826, -0.952379, 0.375, 0.25,
            -0.195222, 2.98516, -0.664616, -0.007398, 0.304826, -0.952379, 0.625, 0.25,
            0.199566, 2.98495, -0.667749, -0.007398, 0.304826, -0.952379, 0.625, 0.5,
            0.199524, 2.97128, -0.672125, -0.007398, 0.304826, -0.952379, 0.375, 0.5,
            0.199524, 2.97128, -0.672125, 0.999966, -0.000423, -0.008257, 0.375, 0.5,
            0.199566, 2.98495, -0.667749, 0.999966, -0.000423, -0.008257, 0.625, 0.5,
            0.200069, 2.96504, -0.605781, 0.999966, -0.000423, -0.008257, 0.625, 0.75,
            0.200027, 2.95139, -0.610194, 0.999966, -0.000423, -0.008257, 0.375, 0.75,
            0.200027, 2.95139, -0.610194, 0.006315, -0.307502, 0.951526, 0.375, 0.75,
            0.200069, 2.96504, -0.605781, 0.006315, -0.307502, 0.951526, 0.625, 0.75,
            -0.194722, 2.96538, -0.603051, 0.006315, -0.307502, 0.951526, 0.625, 1,
            -0.194764, 2.95172, -0.607465, 0.006315, -0.307502, 0.951526, 0.375, 1,
            -0.195264, 2.97149, -0.668992, -0.002928, -0.952087, -0.305812, 0.125, 0.5,
            0.199524, 2.97128, -0.672125, -0.002928, -0.952087, -0.305812, 0.375, 0.5,
            0.200027, 2.95139, -0.610194, -0.002928, -0.952087, -0.305812, 0.375, 0.75,
            -0.194764, 2.95172, -0.607465, -0.002928, -0.952087, -0.305812, 0.125, 0.75,
            0.199566, 2.98495, -0.667749, 0.002928, 0.952087, 0.305813, 0.625, 0.5,
            -0.195222, 2.98516, -0.664616, 0.002928, 0.952087, 0.305813, 0.875, 0.5,
            -0.194722, 2.96538, -0.603051, 0.002928, 0.952087, 0.305813, 0.875, 0.75,
            0.200069, 2.96504, -0.605781, 0.002928, 0.952087, 0.305813, 0.625, 0.75,
            -0.195408, 2.97716, -0.686642, -0.999952, -5.3e-05, 0.009754, 0.375, 0,
            -0.195366, 2.99084, -0.68229, -0.999952, -5.3e-05, 0.009754, 0.625, 0,
            -0.195943, 3.0094, -0.741344, -0.999952, -5.3e-05, 0.009754, 0.625, 0.25,
            -0.195983, 2.99567, -0.745541, -0.999952, -5.3e-05, 0.009754, 0.375, 0.25,
            -0.195983, 2.99567, -0.745541, -0.010299, 0.292333, -0.956261, 0.375, 0.25,
            -0.195943, 3.0094, -0.741344, -0.010299, 0.292333, -0.956261, 0.625, 0.25,
            0.198836, 3.00953, -0.745556, -0.010299, 0.292333, -0.956261, 0.625, 0.5,
            0.198795, 2.9958, -0.749752, -0.010299, 0.292333, -0.956261, 0.375, 0.5,
            0.198795, 2.9958, -0.749752, 0.999952, 5.4e-05, -0.009751, 0.375, 0.5,
            0.198836, 3.00953, -0.745556, 0.999952, 5.4e-05, -0.009751, 0.625, 0.5,
            0.199421, 2.99071, -0.685666, 0.999952, 5.4e-05, -0.009751, 0.625, 0.75,
            0.199379, 2.97703, -0.690018, 0.999952, 5.4e-05, -0.009751, 0.375, 0.75,
            0.199379, 2.97703, -0.690018, 0.008048, -0.303216, 0.952888, 0.375, 0.75,
            0.199421, 2.99071, -0.685666, 0.008048, -0.303216, 0.952888, 0.625, 0.75,
            -0.195366, 2.99084, -0.68229, 0.008048, -0.303216, 0.952888, 0.625, 1,
            -0.195408, 2.97716, -0.686642, 0.008048, -0.303216, 0.952888, 0.375, 1,
            -0.195983, 2.99567, -0.745541, -0.002879, -0.953985, -0.299839, 0.125, 0.5,
            0.198795, 2.9958, -0.749752, -0.002879, -0.953985, -0.299839, 0.375, 0.5,
            0.199379, 2.97703, -0.690018, -0.002879, -0.953985, -0.299839, 0.375, 0.75,
            -0.195408, 2.97716, -0.686642, -0.002879, -0.953985, -0.299839, 0.125, 0.75,
            0.198836, 3.00953, -0.745556, 0.002879, 0.953987, 0.299834, 0.625, 0.5,
            -0.195943, 3.0094, -0.741344, 0.002879, 0.953987, 0.299834, 0.875, 0.5,
            -0.195366, 2.99084, -0.68229, 0.002879, 0.953987, 0.299834, 0.875, 0.75,
            0.199421, 2.99071, -0.685666, 0.002879, 0.953987, 0.299834, 0.625, 0.75,
            -0.196172, 3.00113, -0.763229, -0.999923, -0.000853, 0.012377, 0.375, 0,
            -0.196132, 3.01488, -0.759097, -0.999923, -0.000853, 0.012377, 0.625, 0,
            -0.196884, 3.03222, -0.818652, -0.999923, -0.000853, 0.012377, 0.625, 0.25,
            -0.196919, 3.01837, -0.822411, -0.999923, -0.000853, 0.012377, 0.375, 0.25,
            -0.196919, 3.01837, -0.822411, -0.013162, 0.261823, -0.965026, 0.375, 0.25,
            -0.196884, 3.03222, -0.818652, -0.013162, 0.261823, -0.965026, 0.625, 0.25,
            0.197881, 3.03266, -0.823917, -0.013162, 0.261823, -0.965026, 0.625, 0.5,
            0.197847, 3.01881, -0.827675, -0.013162, 0.261823, -0.965026, 0.375, 0.5,
            0.197847, 3.01881, -0.827675, 0.999923, 0.000854, -0.012375, 0.375, 0.5,
            0.197881, 3.03266, -0.823917, 0.999923, 0.000854, -0.012375, 0.625, 0.5,
            0.198643, 3.01509, -0.763559, 0.999923, 0.000854, -0.012375, 0.625, 0.75,
            0.198604, 3.00134, -0.767692, 0.999923, 0.000854, -0.012375, 0.375, 0.75,
            0.198604, 3.00134, -0.767692, 0.010977, -0.287888, 0.957601, 0.375, 0.75,
            0.198643, 3.01509, -0.763559, 0.010977, -0.287888, 0.957601, 0.625, 0.75,
            -0.196132, 3.01488, -0.759097, 0.010977, -0.287888, 0.957601, 0.625, 1,
            -0.196172, 3.00113, -0.763229, 0.010977, -0.287888, 0.957601, 0.375, 1,
            -0.196919, 3.01837, -0.822411, -0.002655, -0.96013, -0.279542, 0.125, 0.5,
            0.197847, 3.01881, -0.827675, -0.002655, -0.96013, -0.279542, 0.375, 0.5,
            0.198604, 3.00134, -0.767692, -0.002655, -0.96013, -0.279542, 0.375, 0.75,
            -0.196172, 3.00113, -0.763229, -0.002655, -0.96013, -0.279542, 0.125, 0.75,
            0.197881, 3.03266, -0.823917, 0.002655, 0.960138, 0.279513, 0.625, 0.5,
            -0.196884, 3.03222, -0.818652, 0.002655, 0.960138, 0.279513, 0.875, 0.5,
            -0.196132, 3.01488, -0.759097, 0.002655, 0.960138, 0.279513, 0.875, 0.75,
            0.198643, 3.01509, -0.763559, 0.002655, 0.960138, 0.279513, 0.625, 0.75,
            -0.197181, 3.02291, -0.84032, -0.999892, -0.001452, 0.014608, 0.375, 0,
            -0.197149, 3.03681, -0.83676, -0.999892, -0.001452, 0.014608, 0.625, 0,
            -0.198057, 3.051, -0.897505, -0.999892, -0.001452, 0.014608, 0.625, 0.25,
            -0.198077, 3.03692, -0.900277, -0.999892, -0.001452, 0.014608, 0.375, 0.25,
            -0.198077, 3.03692, -0.900277, -0.014974, 0.193086, -0.981068, 0.375, 0.25,
            -0.198057, 3.051, -0.897505, -0.014974, 0.193086, -0.981068, 0.625, 0.25,
            0.196699, 3.0516, -0.903412, -0.014974, 0.193086, -0.981068, 0.625, 0.5,
            0.196679, 3.03752, -0.906183, -0.014974, 0.193086, -0.981068, 0.375, 0.5,
            0.196679, 3.03752, -0.906183, 0.999892, 0.001451, -0.014606, 0.375, 0.5,
            0.196699, 3.0516, -0.903412, 0.999892, 0.001451, -0.014606, 0.625, 0.5,
            0.197614, 3.0373, -0.842207, 0.999892, 0.001451, -0.014606, 0.625, 0.75,
            0.197582, 3.0234, -0.845766, 0.999892, 0.001451, -0.014606, 0.375, 0.75,
            0.197582, 3.0234, -0.845766, 0.013672, -0.247984, 0.968668, 0.375, 0.75,
            0.197614, 3.0373, -0.842207, 0.013672, -0.247984, 0.968668, 0.625, 0.75,
            -0.197149, 3.03681, -0.83676, 0.013672, -0.247984, 0.968668, 0.625, 1,
            -0.197181, 3.02291, -0.84032, 0.013672, -0.247984, 0.968668, 0.375, 1,
            -0.198077, 3.03692, -0.900277, -0.001926, -0.973758, -0.22758, 0.125, 0.5,
            0.196679, 3.03752, -0.906183, -0.001926, -0.973758, -0.22758, 0.375, 0.5,
            0.197582, 3.0234, -0.845766, -0.001926, -0.973758, -0.22758, 0.375, 0.75,
            -0.197181, 3.02291, -0.84032, -0.001926, -0.973758, -0.22758, 0.125, 0.75,
            0.196699, 3.0516, -0.903412, 0.001925, 0.973779, 0.22749, 0.625, 0.5,
            -0.198057, 3.051, -0.897505, 0.001925, 0.973779, 0.22749, 0.875, 0.5,
            -0.197149, 3.03681, -0.83676, 0.001925, 0.973779, 0.22749, 0.875, 0.75,
            0.197614, 3.0373, -0.842207, 0.001925, 0.973779, 0.22749, 0.625, 0.75,
            -0.198362, 3.04036, -0.918439, -0.999885, -0.001544, 0.015065, 0.375, 0,
            -0.198347, 3.05451, -0.915987, -0.999885, -0.001544, 0.015065, 0.625, 0,
            -0.1993, 3.06292, -0.978403, -0.999885, -0.001544, 0.015065, 0.625, 0.25,
            -0.199296, 3.04861, -0.979562, -0.999885, -0.001544, 0.015065, 0.375, 0.25,
            -0.199296, 3.04861, -0.979562, -0.014283, 0.080704, -0.996636, 0.375, 0.25,
            -0.1993, 3.06292, -0.978403, -0.014283, 0.080704, -0.996636, 0.625, 0.25,
            0.195461, 3.0635, -0.984013, -0.014283, 0.080704, -0.996636, 0.625, 0.5,
            0.195465, 3.04919, -0.985172, -0.014283, 0.080704, -0.996636, 0.375, 0.5,
            0.195465, 3.04919, -0.985172, 0.999885, 0.001543, -0.015067, 0.375, 0.5,
            0.195461, 3.0635, -0.984013, 0.999885, 0.001543, -0.015067, 0.625, 0.5,
            0.196409, 3.05512, -0.921932, 0.999885, 0.001543, -0.015067, 0.625, 0.75,
            0.196394, 3.04097, -0.924384, 0.999885, 0.001543, -0.015067, 0.375, 0.75,
            0.196394, 3.04097, -0.924384, 0.015101, -0.170813, 0.985188, 0.375, 0.75,
            0.196409, 3.05512, -0.921932, 0.015101, -0.170813, 0.985188, 0.625, 0.75,
            -0.198347, 3.05451, -0.915987, 0.015101, -0.170813, 0.985188, 0.625, 1,
            -0.198362, 3.04036, -0.918439, 0.015101, -0.170813, 0.985188, 0.375, 1,
            -0.199296, 3.04861, -0.979562, -0.000463, -0.990997, -0.133885, 0.125, 0.5,
            0.195465, 3.04919, -0.985172, -0.000463, -0.990997, -0.133885, 0.375, 0.5,
            0.196394, 3.04097, -0.924384, -0.000463, -0.990997, -0.133885, 0.375, 0.75,
            -0.198362, 3.04036, -0.918439, -0.000463, -0.990997, -0.133885, 0.125, 0.75,
            0.195461, 3.0635, -0.984013, 0.000461, 0.991019, 0.13372, 0.625, 0.5,
            -0.1993, 3.06292, -0.978403, 0.000461, 0.991019, 0.13372, 0.875, 0.5,
            -0.198347, 3.05451, -0.915987, 0.000461, 0.991019, 0.13372, 0.875, 0.75,
            0.196409, 3.05512, -0.921932, 0.000461, 0.991019, 0.13372, 0.625, 0.75,
            -0.199572, 3.05041, -0.998021, -0.999927, -0.001366, 0.012022, 0.375, 0,
            -0.199583, 3.06474, -0.9973, -0.999927, -0.001366, 0.012022, 0.625, 0,
            -0.200348, 3.0641, -1.06094, -0.999927, -0.001366, 0.012022, 0.625, 0.25,
            -0.200318, 3.04977, -1.06011, -0.999927, -0.001366, 0.012022, 0.375, 0.25,
            -0.200318, 3.04977, -1.06011, -0.010016, -0.05821, -0.998254, 0.375, 0.25,
            -0.200348, 3.0641, -1.06094, -0.010016, -0.05821, -0.998254, 0.625, 0.25,
            0.194433, 3.06469, -1.06494, -0.010016, -0.05821, -0.998254, 0.625, 0.5,
            0.194463, 3.05036, -1.0641, -0.010016, -0.05821, -0.998254, 0.375, 0.5,
            0.194463, 3.05036, -1.0641, 0.999927, 0.001366, -0.012024, 0.375, 0.5,
            0.194433, 3.06469, -1.06494, 0.999927, 0.001366, -0.012024, 0.625, 0.5,
            0.19518, 3.06531, -1.00271, 0.999927, 0.001366, -0.012024, 0.625, 0.75,
            0.195191, 3.05098, -1.00343, 0.999927, 0.001366, -0.012024, 0.375, 0.75,
            0.195191, 3.05098, -1.00343, 0.013761, -0.050257, 0.998642, 0.375, 0.75,
            0.19518, 3.06531, -1.00271, 0.013761, -0.050257, 0.998642, 0.625, 0.75,
            -0.199583, 3.06474, -0.9973, 0.013761, -0.050257, 0.998642, 0.625, 1,
            -0.199572, 3.05041, -0.998021, 0.013761, -0.050257, 0.998642, 0.375, 1,
            -0.200318, 3.04977, -1.06011, 0.001584, -0.999947, 0.01019, 0.125, 0.5,
            0.194463, 3.05036, -1.0641, 0.001584, -0.999947, 0.01019, 0.375, 0.5,
            0.195191, 3.05098, -1.00343, 0.001584, -0.999947, 0.01019, 0.375, 0.75,
            -0.199572, 3.05041, -0.998021, 0.001584, -0.999947, 0.01019, 0.125, 0.75,
            0.194433, 3.06469, -1.06494, -0.001582, 0.999948, -0.010036, 0.625, 0.5,
            -0.200348, 3.0641, -1.06094, -0.001582, 0.999948, -0.010036, 0.875, 0.5,
            -0.199583, 3.06474, -0.9973, -0.001582, 0.999948, -0.010036, 0.875, 0.75,
            0.19518, 3.06531, -1.00271, -0.001582, 0.999948, -0.010036, 0.625, 0.75,
            -0.200492, 3.04836, -1.07873, -0.999977, -0.001802, 0.006488, 0.375, 0,
            -0.200526, 3.06266, -1.08, -0.999977, -0.001802, 0.006488, 0.625, 0,
            -0.20092, 3.05376, -1.14315, -0.999977, -0.001802, 0.006488, 0.625, 0.25,
            -0.200877, 3.03964, -1.14059, -0.999977, -0.001802, 0.006488, 0.375, 0.25,
            -0.200877, 3.03964, -1.14059, -0.003692, -0.178568, -0.983921, 0.375, 0.25,
            -0.20092, 3.05376, -1.14315, -0.003692, -0.178568, -0.983921, 0.625, 0.25,
            0.193877, 3.05465, -1.14479, -0.003692, -0.178568, -0.983921, 0.625, 0.5,
            0.193919, 3.04052, -1.14223, -0.003692, -0.178568, -0.983921, 0.375, 0.5,
            0.193919, 3.04052, -1.14223, 0.999977, 0.001802, -0.006487, 0.375, 0.5,
            0.193877, 3.05465, -1.14479, 0.999977, 0.001802, -0.006487, 0.625, 0.5,
            0.194259, 3.06329, -1.08349, 0.999977, 0.001802, -0.006487, 0.625, 0.75,
            0.194293, 3.04899, -1.08221, 0.999977, 0.001802, -0.006487, 0.375, 0.75,
            0.194293, 3.04899, -1.08221, 0.008661, 0.088751, 0.996016, 0.375, 0.75,
            0.194259, 3.06329, -1.08349, 0.008661, 0.088751, 0.996016, 0.625, 0.75,
            -0.200526, 3.06266, -1.08, 0.008661, 0.088751, 0.996016, 0.625, 1,
            -0.200492, 3.04836, -1.07873, 0.008661, 0.088751, 0.996016, 0.375, 1,
            -0.200877, 3.03964, -1.14059, 0.002797, -0.990197, 0.139647, 0.125, 0.5,
            0.193919, 3.04052, -1.14223, 0.002797, -0.990197, 0.139647, 0.375, 0.5,
            0.194293, 3.04899, -1.08221, 0.002797, -0.990197, 0.139647, 0.375, 0.75,
            -0.200492, 3.04836, -1.07873, 0.002797, -0.990197, 0.139647, 0.125, 0.75,
            0.193877, 3.05465, -1.14479, -0.002796, 0.990215, -0.139525, 0.625, 0.5,
            -0.20092, 3.05376, -1.14315, -0.002796, 0.990215, -0.139525, 0.875, 0.5,
            -0.200526, 3.06266, -1.08, -0.002796, 0.990215, -0.139525, 0.875, 0.75,
            0.194259, 3.06329, -1.08349, -0.002796, 0.990215, -0.139525, 0.625, 0.75,
            -0.200909, 3.03567, -1.15895, -0.999995, -0.002966, 0.00055, 0.375, 0,
            -0.200952, 3.04974, -1.16181, -0.999995, -0.002966, 0.00055, 0.625, 0,
            -0.200942, 3.0349, -1.22355, -0.999995, -0.002966, 0.00055, 0.625, 0.25,
            -0.200898, 3.02103, -1.21985, -0.999995, -0.002966, 0.00055, 0.375, 0.25,
            -0.200898, 3.02103, -1.21985, 0.002254, -0.257635, -0.96624, 0.375, 0.25,
            -0.200942, 3.0349, -1.22355, 0.002254, -0.257635, -0.96624, 0.625, 0.25,
            0.193856, 3.03628, -1.223, 0.002254, -0.257635, -0.96624, 0.625, 0.5,
            0.1939, 3.02241, -1.2193, 0.002254, -0.257635, -0.96624, 0.375, 0.5,
            0.1939, 3.02241, -1.2193, 0.999995, 0.002967, -0.000546, 0.375, 0.5,
            0.193856, 3.03628, -1.223, 0.999995, 0.002967, -0.000546, 0.625, 0.5,
            0.193847, 3.05072, -1.16292, 0.999995, 0.002967, -0.000546, 0.625, 0.75,
            0.19389, 3.03666, -1.16006, 0.999995, 0.002967, -0.000546, 0.375, 0.75,
            0.19389, 3.03666, -1.16006, 0.002256, 0.198899, 0.980017, 0.375, 0.75,
            0.193847, 3.05072, -1.16292, 0.002256, 0.198899, 0.980017, 0.625, 0.75,
            -0.200952, 3.04974, -1.16181, 0.002256, 0.198899, 0.980017, 0.625, 1,
            -0.200909, 3.03567, -1.15895, 0.002256, 0.198899, 0.980017, 0.375, 1,
            -0.200898, 3.02103, -1.21985, 0.003078, -0.97229, 0.233756, 0.125, 0.5,
            0.1939, 3.02241, -1.2193, 0.003078, -0.97229, 0.233756, 0.375, 0.5,
            0.19389, 3.03666, -1.16006, 0.003078, -0.97229, 0.233756, 0.375, 0.75,
            -0.200909, 3.03567, -1.15895, 0.003078, -0.97229, 0.233756, 0.125, 0.75,
            0.193856, 3.03628, -1.223, -0.003078, 0.972308, -0.233681, 0.625, 0.5,
            -0.200942, 3.0349, -1.22355, -0.003078, 0.972308, -0.233681, 0.875, 0.5,
            -0.200952, 3.04974, -1.16181, -0.003078, 0.972308, -0.233681, 0.875, 0.75,
            0.193847, 3.05072, -1.16292, -0.003078, 0.972308, -0.233681, 0.625, 0.75,
            -0.200843, 3.016, -1.23797, -0.999981, -0.00432, -0.004324, 0.375, 0,
            -0.200886, 3.02981, -1.24186, -0.999981, -0.00432, -0.004324, 0.625, 0,
            -0.200545, 3.01135, -1.30229, -0.999981, -0.00432, -0.004324, 0.625, 0.25,
            -0.200505, 2.99769, -1.2979, -0.999981, -0.00432, -0.004324, 0.375, 0.25,
            -0.200505, 2.99769, -1.2979, 0.007061, -0.306443, -0.951863, 0.375, 0.25,
            -0.200545, 3.01135, -1.30229, 0.007061, -0.306443, -0.951863, 0.625, 0.25,
            0.194245, 3.01325, -1.29998, 0.007061, -0.306443, -0.951863, 0.625, 0.5,
            0.194285, 2.99959, -1.29558, 0.007061, -0.306443, -0.951863, 0.375, 0.5,
            0.194285, 2.99959, -1.29558, 0.999981, 0.004321, 0.004326, 0.375, 0.5,
            0.194245, 3.01325, -1.29998, 0.999981, 0.004321, 0.004326, 0.625, 0.5,
            0.193911, 3.03132, -1.24086, 0.999981, 0.004321, 0.004326, 0.625, 0.75,
            0.193954, 3.0175, -1.23697, 0.999981, 0.004321, 0.004326, 0.375, 0.75,
            0.193954, 3.0175, -1.23697, -0.003477, 0.271238, 0.962506, 0.375, 0.75,
            0.193911, 3.03132, -1.24086, -0.003477, 0.271238, 0.962506, 0.625, 0.75,
            -0.200886, 3.02981, -1.24186, -0.003477, 0.271238, 0.962506, 0.625, 1,
            -0.200843, 3.016, -1.23797, -0.003477, 0.271238, 0.962506, 0.375, 1,
            -0.200505, 2.99769, -1.2979, 0.0029, -0.956342, 0.292235, 0.125, 0.5,
            0.194285, 2.99959, -1.29558, 0.0029, -0.956342, 0.292235, 0.375, 0.5,
            0.193954, 3.0175, -1.23697, 0.0029, -0.956342, 0.292235, 0.375, 0.75,
            -0.200843, 3.016, -1.23797, 0.0029, -0.956342, 0.292235, 0.125, 0.75,
            0.194245, 3.01325, -1.29998, -0.0029, 0.956351, -0.292207, 0.625, 0.5,
            -0.200545, 3.01135, -1.30229, -0.0029, 0.956351, -0.292207, 0.875, 0.5,
            -0.200886, 3.02981, -1.24186, -0.0029, 0.956351, -0.292207, 0.875, 0.75,
            0.193911, 3.03132, -1.24086, -0.0029, 0.956351, -0.292207, 0.625, 0.75,
            -0.200381, 2.99197, -1.31581, -0.999954, -0.00547, -0.00784, 0.375, 0,
            -0.20042, 3.00559, -1.32034, -0.999954, -0.00547, -0.00784, 0.625, 0,
            -0.199841, 2.98509, -1.37987, -0.999954, -0.00547, -0.00784, 0.625, 0.25,
            -0.199805, 2.97158, -1.37503, -0.999954, -0.00547, -0.00784, 0.375, 0.25,
            -0.199805, 2.97158, -1.37503, 0.010872, -0.337103, -0.941405, 0.375, 0.25,
            -0.199841, 2.98509, -1.37987, 0.010872, -0.337103, -0.941405, 0.625, 0.25,
            0.194936, 2.98747, -1.37616, 0.010872, -0.337103, -0.941405, 0.625, 0.5,
            0.194972, 2.97395, -1.37132, 0.010872, -0.337103, -0.941405, 0.375, 0.5,
            0.194972, 2.97395, -1.37132, 0.999954, 0.005469, 0.007837, 0.375, 0.5,
            0.194936, 2.98747, -1.37616, 0.999954, 0.005469, 0.007837, 0.625, 0.5,
            0.194367, 3.00761, -1.31765, 0.999954, 0.005469, 0.007837, 0.625, 0.75,
            0.194406, 2.99399, -1.31312, 0.999954, 0.005469, 0.007837, 0.375, 0.75,
            0.194406, 2.99399, -1.31312, -0.008064, 0.315501, 0.948891, 0.375, 0.75,
            0.194367, 3.00761, -1.31765, -0.008064, 0.315501, 0.948891, 0.625, 0.75,
            -0.20042, 3.00559, -1.32034, -0.008064, 0.315501, 0.948891, 0.625, 1,
            -0.200381, 2.99197, -1.31581, -0.008064, 0.315501, 0.948891, 0.375, 1,
            -0.199805, 2.97158, -1.37503, 0.002636, -0.945513, 0.325574, 0.125, 0.5,
            0.194972, 2.97395, -1.37132, 0.002636, -0.945513, 0.325574, 0.375, 0.5,
            0.194406, 2.99399, -1.31312, 0.002636, -0.945513, 0.325574, 0.375, 0.75,
            -0.200381, 2.99197, -1.31581, 0.002636, -0.945513, 0.325574, 0.125, 0.75,
            0.194936, 2.98747, -1.37616, -0.002636, 0.945511, -0.325579, 0.625, 0.5,
            -0.199841, 2.98509, -1.37987, -0.002636, 0.945511, -0.325579, 0.875, 0.5,
            -0.20042, 3.00559, -1.32034, -0.002636, 0.945511, -0.325579, 0.875, 0.75,
            0.194367, 3.00761, -1.31765, -0.002636, 0.945511, -0.325579, 0.625, 0.75
    };

    unsigned int m_indices[3 * 120] = {
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            4, 6, 7,
            8, 9, 10,
            8, 10, 11,
            12, 13, 14,
            12, 14, 15,
            16, 17, 18,
            16, 18, 19,
            20, 21, 22,
            20, 22, 23,
            24, 25, 26,
            24, 26, 27,
            28, 29, 30,
            28, 30, 31,
            32, 33, 34,
            32, 34, 35,
            36, 37, 38,
            36, 38, 39,
            40, 41, 42,
            40, 42, 43,
            44, 45, 46,
            44, 46, 47,
            48, 49, 50,
            48, 50, 51,
            52, 53, 54,
            52, 54, 55,
            56, 57, 58,
            56, 58, 59,
            60, 61, 62,
            60, 62, 63,
            64, 65, 66,
            64, 66, 67,
            68, 69, 70,
            68, 70, 71,
            72, 73, 74,
            72, 74, 75,
            76, 77, 78,
            76, 78, 79,
            80, 81, 82,
            80, 82, 83,
            84, 85, 86,
            84, 86, 87,
            88, 89, 90,
            88, 90, 91,
            92, 93, 94,
            92, 94, 95,
            96, 97, 98,
            96, 98, 99,
            100, 101, 102,
            100, 102, 103,
            104, 105, 106,
            104, 106, 107,
            108, 109, 110,
            108, 110, 111,
            112, 113, 114,
            112, 114, 115,
            116, 117, 118,
            116, 118, 119,
            120, 121, 122,
            120, 122, 123,
            124, 125, 126,
            124, 126, 127,
            128, 129, 130,
            128, 130, 131,
            132, 133, 134,
            132, 134, 135,
            136, 137, 138,
            136, 138, 139,
            140, 141, 142,
            140, 142, 143,
            144, 145, 146,
            144, 146, 147,
            148, 149, 150,
            148, 150, 151,
            152, 153, 154,
            152, 154, 155,
            156, 157, 158,
            156, 158, 159,
            160, 161, 162,
            160, 162, 163,
            164, 165, 166,
            164, 166, 167,
            168, 169, 170,
            168, 170, 171,
            172, 173, 174,
            172, 174, 175,
            176, 177, 178,
            176, 178, 179,
            180, 181, 182,
            180, 182, 183,
            184, 185, 186,
            184, 186, 187,
            188, 189, 190,
            188, 190, 191,
            192, 193, 194,
            192, 194, 195,
            196, 197, 198,
            196, 198, 199,
            200, 201, 202,
            200, 202, 203,
            204, 205, 206,
            204, 206, 207,
            208, 209, 210,
            208, 210, 211,
            212, 213, 214,
            212, 214, 215,
            216, 217, 218,
            216, 218, 219,
            220, 221, 222,
            220, 222, 223,
            224, 225, 226,
            224, 226, 227,
            228, 229, 230,
            228, 230, 231,
            232, 233, 234,
            232, 234, 235,
            236, 237, 238,
            236, 238, 239
    };
};