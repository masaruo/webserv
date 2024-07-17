/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_gtest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:12:22 by mogawa            #+#    #+#             */
/*   Updated: 2023/10/20 07:28:52 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sample.class.hpp"
#include "gtest/gtest.h"

// c++ -std=c++17 Sample.class.cpp Sample.unitest.cpp -lpthread -lgtest_main -lgtest

namespace
{
	TEST(Sample, DefaultConstructor)
	{
		Sample const	s(3.14f);
		EXPECT_FLOAT_EQ(3.14f, s.pi);
		EXPECT_EQ(42, s.qd);
	}

	TEST(Sample, Print)
	{
		Sample const	s(3.14f);
		testing::internal::CaptureStdout();
		s.print();
		EXPECT_STREQ("41", testing::internal::GetCapturedStdout().c_str());
	}
}