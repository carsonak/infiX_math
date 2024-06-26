#include "tests.h"

u4b_array num1 = {.len = 0, .is_negative = 0, .array = NULL};
u4b_array num2 = {.len = 0, .is_negative = 0, .array = NULL};
u4b_array expected = {.len = 0, .is_negative = 0, .array = NULL};

/**
 * infiX_addition - Dummy
 * @n1: unused
 * @n2: unused
 *
 * Return: NULL always.
 */
u4b_array *infiX_addition(u4b_array *n1, u4b_array *n2)
{
	(void)n1;
	(void)n2;
	return (alloc_u4b_array(0));
}

/**
 * setup - initialises variables for tests.
 */
void setup(void) {}

/**
 * teardown - resets variables for tests.
 */
void teardown(void)
{
	num1.len = 0;
	num1.is_negative = 0;
	num1.array = NULL;

	num2.len = 0;
	num2.is_negative = 0;
	num2.array = NULL;

	expected.len = 0;
	expected.is_negative = 0;
	expected.array = NULL;
}

TestSuite(null_inputs, .init = setup, .fini = teardown);

Test(null_inputs, test_null_minus_null,
	 .description = "NULL - NULL = NULL", .timeout = 2.0)
{
	u4b_array *output = infiX_subtraction(NULL, NULL);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_1_minus_null,
	 .description = "1 - NULL = NULL", .timeout = 2.0)
{
	uint32_t in1[] = {1};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	u4b_array *output = infiX_subtraction(&num1, NULL);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_null_minus_1,
	 .description = "NULL - 1 = NULL", .timeout = 2.0)
{
	uint32_t in2[] = {1};

	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	u4b_array *output = infiX_subtraction(NULL, &num2);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_0_minus_null,
	 .description = "0 - NULL = NULL", .timeout = 2.0)
{
	uint32_t in1[] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	u4b_array *output = infiX_subtraction(&num1, NULL);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_null_minus_0,
	 .description = "NULL - 0 = NULL", .timeout = 2.0)
{
	uint32_t in2[] = {0};

	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	u4b_array *output = infiX_subtraction(NULL, &num2);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_minus1_minus_null,
	 .description = "-1 - NULL = NULL", .timeout = 2.0)
{
	uint32_t in1[] = {1};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num1.is_negative = 1;
	u4b_array *output = infiX_subtraction(&num1, NULL);

	cr_expect(zero(ptr, output));
}

Test(null_inputs, test_null_minus_minus1,
	 .description = "NULL - -1 = NULL", .timeout = 2.0)
{
	uint32_t in2[] = {1};

	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	num2.is_negative = 1;
	u4b_array *output = infiX_subtraction(NULL, &num2);

	cr_expect(zero(ptr, output));
}

TestSuite(zero_len_arrays, .init = setup, .fini = teardown);

Test(zero_len_arrays, test_null_minus_null,
	 .description = "null_array - null_array = null_array", .timeout = 2.0)
{
	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(zero(sz, output->len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(zero(ptr, output->array));
	output = free_u4b_array(output);
}

Test(zero_len_arrays, test_4490998_minus_null,
	 .description = "4,490,998 - null_array = 4,490,998", .timeout = 2.0)
{
	uint32_t in1[] = {4490998}, out[] = {4490998};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	expected.len = sizeof(out) / sizeof(*out);
	expected.array = out;
	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(zero_len_arrays, test_null_minus_largenum,
	 .description = "null_array - 99992175,712000569,0,0,6086,232509426,238542068 = -99992175,712000569,0,0,6086,232509426,238542068",
	 .timeout = 2.0)
{
	uint32_t in2[] = {238542068, 232509426, 6086, 0, 0, 712000569, 99992175};
	uint32_t out[] = {238542068, 232509426, 6086, 0, 0, 712000569, 99992175};

	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.is_negative = 1;
	expected.array = out;
	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

TestSuite(simple_subtractions, .init = setup, .fini = teardown);

Test(simple_subtractions, test_0_minus_0,
	 .description = "0 - 0 = 0", .timeout = 2.0)
{
	uint32_t in1[] = {0}, in2[] = {0}, out[] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.array = out;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(simple_subtractions, test_1_minus_0,
	 .description = "1 - 0 = 1", .timeout = 2.0)
{
	uint32_t in1[] = {1}, in2[] = {0}, out[] = {1};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.array = out;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(simple_subtractions, test_0_minus_1,
	 .description = "0 - 1 = -1", .timeout = 2.0)
{
	uint32_t in1[] = {0}, in2[] = {1}, out[] = {1};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.is_negative = 1;
	expected.array = out;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(simple_subtractions, test_1_minus_1,
	 .description = "1 - 1 = 0", .timeout = 2.0)
{
	uint32_t in1[] = {1}, in2[] = {1}, out[] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.array = out;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(simple_subtractions, test_1000000000_minus_minus50000,
	 .description = "1,0 - 50,000 = 999,950,000",
	 .timeout = 2.0)
{
	uint32_t in1[] = {0, 1}, in2[] = {50000}, out[] = {999950000};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.array = out;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(simple_subtractions, test_50000_minus_100000000,
	 .description = "50,000 - 1,000,000,000 = -999,950,000",
	 .timeout = 2.0)
{
	uint32_t in1[] = {50000}, in2[] = {0, 1}, out[] = {999950000};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.is_negative = 1;
	expected.array = out;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(simple_subtractions, test_4000000000678_minus_999999000,
	 .description = "4000,678 - 999,999,000 = 3999,1678",
	 .timeout = 2.0)
{
	uint32_t in1[] = {678, 4000}, in2[] = {999999000}, out[] = {1678, 3999};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.array = out;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(simple_subtractions, test_999999000_minus_4000000000678,
	 .description = "999,999,000 - 4000,678 = -3999,1678",
	 .timeout = 2.0)
{
	uint32_t in1[] = {999999000}, in2[] = {678, 4000}, out[] = {1678, 3999};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.is_negative = 1;
	expected.array = out;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

TestSuite(negative_subtractions, .init = setup, .fini = teardown);

Test(negative_subtractions, test_minus1_minus_minus1,
	 .description = "-1 - -1 = 0", .timeout = 2.0)
{
	uint32_t in1[] = {1}, in2[] = {1}, out[] = {0};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.is_negative = 1;
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.is_negative = 1;
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.array = out;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(negative_subtractions, test_1_minus_minus1,
	 .description = "1 - -1 = 0 (does addition)", .timeout = 2.0)
{
	uint32_t in1[] = {1}, in2[] = {1};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.is_negative = 1;
	num2.array = in2;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(zero(chr, output->is_negative));
	output = free_u4b_array(output);
}

Test(negative_subtractions, test_minus1_minus_1,
	 .description = "-1 - 1 = -2(does addition)", .timeout = 2.0)
{
	uint32_t in1[] = {1}, in2[] = {1};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.is_negative = 1;
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.is_negative = 1;

	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(chr, output->is_negative, expected.is_negative));
	output = free_u4b_array(output);
}

TestSuite(large_subtractions, .init = setup, .fini = teardown);

Test(large_subtractions, test_largenum1_minus_largenum2,
	 .description = "large1 - large2 = large3", .timeout = 2.0)
{
	uint32_t in1[] = {645836236, 108893430, 836208119, 270771001, 537613755, 373039867, 833294108, 898839418, 608485063, 546188873, 452231917, 687296422, 111111152, 111111111, 111111111, 111111111, 111111111, 111111111, 111111111, 111111111, 111111111, 111111111, 476411111, 5669047, 700035645, 893473278, 4493, 543630640, 324000, 568376700, 1394, 300000000, 378345892, 8, 734194700, 423768, 0, 445197384, 518101037, 109617878, 558156514, 983336821, 690076644, 693516675, 143226629, 76588580, 210759419, 973911560, 497333540, 14322213, 555048869, 815323758, 539167661, 458688023, 612425259, 624332483, 419554373, 679371075, 393235000, 236728315, 664373133, 150410609, 518660305, 359239326, 307363945, 571210805, 347785534, 563445710, 660409386, 228008317, 804462179, 233074148, 591937180, 160409198, 950235053, 962974549, 171857157, 523072994, 395079814, 321058488, 203652900, 126072395, 363107953, 630915068, 973080517, 612433363, 734409773, 377726669, 707225937, 627074076, 918808553, 941285428, 110569912, 430944738, 394600177, 990968620, 4498198, 265970467, 594659210, 881718792, 749254660, 489225907, 417635079, 182995180, 494838468, 16834009, 911110449, 948701330, 831191398, 792151714, 70940218, 627665839, 410612359, 202045867, 935804051, 937850141, 227018012, 991791152, 506752363, 406483698, 355792683, 47491630, 22359011, 919962818, 955165934, 399211808, 673319428, 319818160, 662785141, 175882430, 630322415, 735383534, 687650610, 46582669, 496678148, 491637987, 871575195, 116330034, 723314187, 385420689, 325094262, 12829142, 208703866, 120005690, 899921757, 77002169, 359486189, 753454258, 278911354, 694037307, 578519296, 494600786, 470779501, 768446187, 472669563, 716361937, 389127515, 976446119, 593192334, 617083917, 272976737, 418747631, 855714255, 226105187, 605917499, 696971445, 573117854, 99153257, 956645492, 728520292, 946389174, 245482697, 655465609, 470307816, 135416351, 729216591, 866144546, 888959338, 809402688, 527131609, 866613186, 419167460, 916600904, 633154349, 747140489, 315862951, 238759183, 148584074, 652667824, 161606397, 677427537, 590777629, 825244648, 835356427, 366982335, 748040826, 852122159, 4896, 900000000, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 999999999, 385820199, 167580321, 134092496, 277075937, 872169008, 64325722, 827080282, 277960712, 655352740, 163131699, 448213684, 277128786, 514326330, 933871396, 63154105, 745922799, 490015860, 252229607, 711956623, 591788040, 954758766, 467124003, 644524713, 690634208, 510828673, 629041620, 704066384, 468512842, 590156377, 509105852, 101803594, 777808979, 519622805, 972925209, 333284887, 366099858, 584319133, 851605740, 743738793, 912271659, 205902321, 306768696, 951511006, 853007337, 793747247, 858293618, 953587774, 433638706, 827128463, 10931106, 238240138, 541935268, 774418024, 534563619, 736369239, 336516542, 723202909, 72035747, 712282212, 121201039, 863656439, 738195137, 536402352, 988504044, 143816789, 991215483, 635637328, 796292638, 712577246, 870774981, 572335077, 92461651, 417842402, 465754445, 443219011, 441495263, 360383390, 613384414, 161967625, 730605620, 45166037, 501067481, 119816381, 482382428, 993423658, 444792073, 338718477, 357679842, 186546204, 725908514, 242243363, 998754918, 228221686, 517265463, 874612151, 181719511, 64245869, 179742910, 880842840, 733045974, 909570009, 761337985, 469116507, 501497182, 26189637, 141834727, 777673597, 739280728, 284499268, 848912007, 618450280, 855914917, 508218929, 64124951, 440691829, 852588078, 555626401, 202070759, 783604366, 202777713, 212620403, 857142928, 324004839, 349402718, 847565789, 52519590, 658472794, 842462660, 791141310, 195364150, 381999943, 261729562, 18229};
	uint32_t in2[] = {120720357, 397122822, 391212010, 378636564, 527381951, 445364023, 899885040, 831438167, 289912154, 386356373, 467962926, 817125772, 778707749, 515723350, 20924616, 454178424, 114657544, 634432190, 904414952, 143603833, 256133844, 201619676, 377306056, 810451660, 815010674, 281198163, 584823824, 739934236, 774447920, 423387184, 43576798, 141865462, 637259085, 182422433, 869987549, 632282216, 515172654, 118746121, 691817195, 100642458, 401797429, 748808428, 97330459, 859095700, 77613379, 824691165, 375014971, 270261896, 971418347, 287776735, 687392807, 72844992, 808489120, 176184502, 298559149, 515082189, 290641249, 784406918, 18525880, 595556264, 662020707, 137836043, 32027777, 282126204, 398571429, 183240048, 893494027, 908475657, 210325195, 41368093, 567494670, 78549187, 829867982, 939611731, 556446171, 260470617, 388185363, 898568742, 584926832, 930685864, 974259747, 196534676, 548532814, 760521395, 176790149, 995282978, 514569063, 129660418, 873623608, 869739334, 116299016, 931525892, 602082336, 842229732, 82941119, 584280220, 738070679, 549296857, 554682269, 129930289, 352088067, 846285574, 807033108, 924619988, 410518654, 524776378, 210726853, 338324773, 234371231, 345598217, 215913853, 40125185, 169659817, 614457144, 263430597, 839552963, 357693985, 358911228, 31559180, 973973025, 529509086, 130265707, 902771569, 939005219, 909614411, 481137671, 453755527, 315076922, 190488385, 858980849, 914750855, 893492457, 44932638, 537640698, 831905869, 686543771, 164968285, 32694655, 549006585, 907130711, 937753741, 473161761, 60159427, 193787354, 490610706, 977776760, 692607694, 6731141, 102078922, 359416565, 975892579, 663415745, 486552688, 501065002, 401362961, 293547871, 954030315, 717222449, 171804201, 933246578, 628660373, 388008411, 546067821, 318550725, 990682255, 492064339, 647433279, 137385221, 703102597, 102835383, 283915020, 951593059, 607687526, 836935402, 684651719, 23912707, 349733186, 901432221, 855504886, 181532375, 353916766, 945868802, 361242525, 362433248, 541955437, 67937107, 539323500, 323672831, 966437313, 515041060, 651866030, 535923932, 530736394, 457121080, 34778553, 656344571, 766040938, 922800831, 880446217, 23307414, 859193718, 316040919, 995023505, 796297454, 417185715, 452307299, 839507981, 32105848, 520365290, 312607239, 836310795, 763091506, 397308051, 361243336, 973440977, 737772666, 670722593, 362707407, 891880855, 294128542, 811056991, 743094473, 39460017, 899096862, 700449819, 26597046, 259465921, 88171879, 774925466, 948922590, 41763507, 818299518, 949483846, 901683400, 91111044, 894870133, 483119139, 879215171, 907094021, 962766583, 741061235, 120204586, 193580405, 293785014, 701801};
	uint32_t out[] = {525115879, 711770608, 444996108, 892134437, 10231803, 927675844, 933409067, 67401250, 318572909, 159832500, 984268991, 870170649, 332403402, 595387760, 90186494, 656932687, 996453566, 476678920, 206696158, 967507277, 854977266, 909491434, 99105054, 195217387, 885024970, 612275114, 415180669, 803696403, 225876079, 144989515, 956424596, 158134537, 741086807, 817577574, 864207150, 368141551, 484827345, 326451262, 826283842, 8975419, 156359085, 234528393, 592746185, 834420975, 65613249, 251897415, 835744447, 703649663, 525915193, 726545477, 867656061, 742478765, 730678541, 282503520, 313866110, 109250294, 128913124, 894964157, 374709119, 641172051, 2352425, 12574566, 486632528, 77113122, 908792516, 387970756, 454291507, 654970052, 450084190, 186640224, 236967509, 154524961, 762069198, 220797466, 393788881, 702503932, 783671794, 624504251, 810152981, 390372623, 229393152, 929537718, 814575138, 870393672, 796290367, 617150385, 219840709, 248066251, 833602329, 757334741, 802509536, 9759536, 508487576, 588715005, 311659057, 406688400, 266427519, 716673609, 39976940, 751788503, 397166593, 642940333, 610601970, 258375191, 84319813, 492057631, 700383595, 610376557, 596820167, 446553497, 855026365, 587540653, 240952542, 587588723, 672373453, 98297178, 869324027, 632879923, 475193183, 432510673, 826283596, 917225922, 119587441, 980957598, 45551522, 918074137, 219563900, 4741238, 472296756, 316901581, 715571559, 841891076, 642717971, 508941971, 664772278, 805094215, 706606909, 83635379, 174307602, 478289978, 387340520, 539667380, 148544438, 926218336, 409311050, 99225409, 666878494, 746723116, 176832432, 334620742, 602626717, 831185040, 984226812, 267381184, 71306602, 422814066, 435097200, 259223669, 421388133, 683837339, 644316363, 30739219, 309646434, 907554462, 615235243, 204907105, 925684575, 961768035, 253542894, 625684909, 662474154, 293889638, 47778082, 633372414, 450764631, 705303883, 516411360, 987527117, 953897801, 345599233, 512696420, 473298658, 555358378, 270721101, 205185052, 247925844, 699435683, 824911242, 686230510, 646565336, 25561506, 54853697, 294508254, 378235347, 332203782, 91696255, 86081221, 77204065, 19553782, 976692585, 140806281, 683959080, 4976494, 203702545, 582814284, 547692700, 160492018, 967894151, 479634709, 73212960, 331269526, 371000989, 879767885, 510925671, 90884745, 89307615, 607238119, 292645332, 271250844, 154085141, 466071795, 771231856, 894411378, 164057243, 45472979, 463418814, 992763686, 623784743, 816862574, 5836175, 425360496, 826225195, 741150361, 609145272, 537930575, 809196251, 985393702, 710941205, 602011830, 139037010, 36747743, 399418219, 779344804, 39499873, 365398057, 584319133, 851605740, 743738793, 912271659, 205902321, 306768696, 951511006, 853007337, 793747247, 858293618, 953587774, 433638706, 827128463, 10931106, 238240138, 541935268, 774418024, 534563619, 736369239, 336516542, 723202909, 72035747, 712282212, 121201039, 863656439, 738195137, 536402352, 988504044, 143816789, 991215483, 635637328, 796292638, 712577246, 870774981, 572335077, 92461651, 417842402, 465754445, 443219011, 441495263, 360383390, 613384414, 161967625, 730605620, 45166037, 501067481, 119816381, 482382428, 993423658, 444792073, 338718477, 357679842, 186546204, 725908514, 242243363, 998754918, 228221686, 517265463, 874612151, 181719511, 64245869, 179742910, 880842840, 733045974, 909570009, 761337985, 469116507, 501497182, 26189637, 141834727, 777673597, 739280728, 284499268, 848912007, 618450280, 855914917, 508218929, 64124951, 440691829, 852588078, 555626401, 202070759, 783604366, 202777713, 212620403, 857142928, 324004839, 349402718, 847565789, 52519590, 658472794, 842462660, 791141310, 195364150, 381999943, 261729562, 18229};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.array = out;
	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}

Test(large_subtractions, test_medium_largenum1_minus_medium_largenum2,
	 .description = "medium_large1 - medium_large2 = medium_large3",
	 .timeout = 2.0)
{
	uint32_t in1[] = {555555555, 55555555, 0, 0, 0, 0, 222222, 0, 0, 0, 0, 0, 0, 0, 0, 888888888, 888888888, 888888888, 888888888, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 110000000, 111111111, 111111111, 111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 770000000, 777777777, 777777777, 777777, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 999000000, 99999999};
	uint32_t in2[] = {470282653, 363502795, 428381283, 187482382, 467199043, 93190808, 0, 0, 0, 400000000, 133986336, 818672645, 328552829, 467844093, 238950876, 737842756, 975675668, 665546560, 147030781, 113541635, 672921659, 886614454, 888895933, 888888888, 888888888, 888888888, 268888888, 160980940, 318652713, 746086661, 442022266, 249623720, 646946071, 524660960, 229717732, 571794052, 616061544, 679629263, 171257724, 787077498, 157233507, 209246165, 541784240, 146575444, 344321901, 44149526, 436038339, 561338441, 16196762, 773060562, 104516603, 150106748, 411981638, 444444444, 444444444, 444444444, 444444444, 444444444, 444444444, 4};
	uint32_t out[] = {85272902, 692052760, 571618716, 812517617, 532800956, 906809191, 222221, 0, 0, 600000000, 866013663, 181327354, 671447170, 532155906, 761049123, 151046131, 913213220, 223342327, 741858107, 886458365, 327078340, 113385545, 111104066, 111111111, 111111111, 111111111, 731111111, 839019059, 681347286, 363913338, 669088844, 861487390, 353054039, 475339039, 770282267, 428205947, 383938455, 320370736, 828742275, 212922501, 842766492, 790753834, 458215759, 853424555, 655678098, 725850473, 341739438, 216439336, 984581015, 226939437, 895483396, 849893251, 588018361, 555555555, 555555555, 555555555, 555555555, 555555555, 555555555, 999999995, 999999999, 999999999, 999999999, 999999999, 998999999, 99999999};

	num1.len = sizeof(in1) / sizeof(*in1);
	num1.array = in1;
	num2.len = sizeof(in2) / sizeof(*in2);
	num2.array = in2;
	expected.len = sizeof(out) / sizeof(*out);
	expected.array = out;
	u4b_array *output = infiX_subtraction(&num1, &num2);

	cr_expect(eq(sz, output->len, expected.len));
	cr_expect(zero(chr, output->is_negative));
	cr_expect(eq(u32[expected.len], output->array, expected.array));
	output = free_u4b_array(output);
}
