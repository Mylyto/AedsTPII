#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "city.h"
#include "path.h"
#include "truck.h"
#include "generator.h"
#include "citystack.h"

START_TEST(test_city_create)
{
	City c;
	initCity(&c,5);
	ck_assert_int_eq(getRequirements(c),5);
	ck_assert_msg(getMetRequirements(c) == 0, "Was expecting met_requirements = 0, but received met_requirements = %d",getMetRequirements(c));
	meetRequirements(&c);
	ck_assert_msg(getMetRequirements(c) == 1, "Was expecting met_requirements = 1, but received met_requirements = %d",getMetRequirements(c));
}
END_TEST
START_TEST(test_citystack_create)
{
	CityStack cs;
	int i;
	City c[5];
	City ctemp;
	initCityStack(&cs);
	for (i = 0; i < 5; i++) {
		initCity(&c[i],i);
		ck_assert_msg(size(&cs)==i,"Expected CityStack size %d Received %d",i,size(&cs) );
		push(&cs,c[i]);
	}
	for (i = 4; i >= 0; i--) {
		ck_assert_msg(size(&cs)==i+1,"Expected CityStack size %d Received %d",i+1,size(&cs) );
		ctemp = c[i];
		pop(&cs,&c[i]);
		ck_assert_msg(ctemp.requirements==c[i].requirements,"Failed during CityStack popping. Value is different from expected");
	}
	unsigned int top;
}
END_TEST
START_TEST(test_path_create)
{
	City c[4];
	int i;
	for (i = 0; i < 4; i++) {
		initCity(&c[i],4+i);
	}
	Path p;
	initPath(&p,c,4);
	ck_assert_msg(getSize(&p)==4,"Expected size 4, received %d",getSize(&p));
	ck_assert_msg(getNextCity(&p).requirements == c[0].requirements ,"Expected c[0] %d and received %d", c[0].requirements, getNextCity(&p).requirements);
	forwardRoute(&p);
	ck_assert_msg(getNextCity(&p).requirements == c[1].requirements ,"Expected c[1 %d and received %d", c[1].requirements, getNextCity(&p).requirements);
	
}
END_TEST
Suite * tads_suite(void){
	Suite *s;
	TCase *tc_city, *tc_citystack, *tc_path;
	s = suite_create("TADS");
	tc_path = tcase_create("Path");
	tc_city = tcase_create("City");
	tc_citystack = tcase_create("CityStack");
	tcase_add_test(tc_path, test_path_create);
	tcase_add_test(tc_city, test_city_create);
	tcase_add_test(tc_citystack, test_citystack_create);
	suite_add_tcase(s,tc_city);
	suite_add_tcase(s,tc_citystack);
	suite_add_tcase(s,tc_path);
	return s;
}
int main(void){
	int number_failed;
	Suite *s;
	SRunner *sr;
	s = tads_suite();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

