include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

ROSE_FLAGS = -rose:verbose 0 -I$(srcdir)

AM_CPPFLAGS = $(ROSE_INCLUDES) 
AM_LDFLAGS = $(ROSE_RPATHS)
LDADD    = $(ROSE_LIBS)

JOVIAL_TESTCODES = \
 tiny.jov                               \
 1_2_3_main-program-module_a.jov        \
 1_2_3_main-program-module_b.jov        \
 1_2_3_program-body_b.jov               \
 1_2_3_program-body_c.jov               \
 2_1_1_5_char_item_desc.jov             \
 2_1_2_simple_table_var.jov             \
 2_1_2_compound_table_var.jov           \
 2_1_2_1_table_dimension_list_a.jov     \
 2_1_2_1_table_dimension_list_b.jov     \
 4_2_loop_stmt_while_a.jov              \
 4_2_loop_stmt_b1.jov                   \
 4_2_loop_stmt_d1.jov                   \
 4_3_if_else_stmt.jov                   \
 4_4_case_stmt_a.jov                    \
 4_6_return_stmt_a.jov                  \
 4_7_goto_stmt_a.jov                    \
 4_8_exit_stmt.jov                      \
 4_9_stop_stmt_a.jov                    \
 4_9_stop_stmt_b.jov                    \
 4_9_stop_stmt_c.jov                    \
 4_10_abort_stmt_a.jov                  \
 4_10_abort_stmt_b.jov                  \
 5_1_1_integer-precedence.jov           \
 5_1_1_integer-primary.jov              \
 5_1_1_integer-term.jov                 \
 5_2_1_relational_expressions_a.jov     \
 9_0_directives.jov                     \
 rose-issue-1507.jov                    \
 rose-issue-1516.jov                    \
 rose-issue-2143.jov

COMPOOL_TESTCODES = \
 2_2_compound_block_type.cpl            \
 2_2_compound_table_type.cpl            \
 2_2_simple_block_type.cpl              \
 2_2_simple_table_type.cpl              \
 2_5_def_ref_item.cpl                   \
 define_dollar.cpl                      \
 status_type.cpl                        \
 rose-issue-1518.cpl                    \
 rose-issue-1520.cpl                    \
 rose-issue-2143.cpl                    \
 rose-issue-2286.cpl

# should finish formulas next
#
JOVIAL_TESTCODES_PASS_TRAVERSE = \
 4_0_compound_stmt_a.jov                \
 4_0_compound_stmt_b.jov                \
 4_0_null_block_stmt.jov                \
 4_3_if_stmt_b.jov                      \
 4_3_if_stmt_c.jov                      \
 4_3_if_stmt_d.jov                      \
 4_3_if_stmt_e.jov                      \
 4_7_goto_stmt_b.jov                    \
 5_3_character_formula_a.jov            \
 5_3_character_formula_b.jov            \
 5_3_character_formula_c.jov            \
 5_3_character_formula_d.jov            \
 5_4_status_formula_a.jov               \
 5_4_status_formula_b.jov               \
 5_4_status_formula_c.jov               \
 5_4_status_formula_d.jov               \
 5_5_pointer_formula_a.jov              \
 5_5_pointer_formula_b.jov              \
 5_5_pointer_formula_c.jov              \
 5_5_pointer_formula_d.jov              \
 table_type.cpl                         \
 rose-issue-2144.cpl

JOVIAL_TESTCODES_WORKING_ON = \
 rose-issue-2100.jov                    \
 rose-issue-2101.jov                    \
 rose-issue-2102.jov                    \
 rose-issue-2104.jov                    \
 rose-issue-2105.jov                    \
 rose-issue-2106.jov                    \
 rose-issue-2107.jov                    \
 rose-issue-2145.jov                    \
 rose-issue-2146.jov                    \
 rose-issue-2147.jov                    \
 rose-issue-2148.jov                    \
 rose-issue-2149.jov                    \
 rose-issue-2150.jov                    \
 1_2_2_non-nested-subroutine_a.jov      \
 1_2_2_non-nested-subroutine_b.jov      \
 1_2_2_procedure-module_a.jov           \
 1_2_2_procedure-module_b.jov           \
 1_2_2_procedure_module_c.jov           \
 1_2_2_procedure_module_d.jov           \
 1_2_2_procedure_module_e.jov           \
 1_2_2_procedure_module_f.jov           \
 1_2_2_procedure_module_g.jov           \
 1_2_3_main-program-module_b.jov        \
 1_2_3_main-program-module_c.jov        \
 1_2_3_main-program-module_d.jov        \
 1_2_3_program-body_a.jov               \
 1_2_3_program-body_d.jov               \
 1_2_3_program-body_e.jov               \
 1_2_3_program-body_f.jov               \
 1_2_3_program-body_g.jov               \
 1_2_3_program-body_h.jov               \
 4_1_assignment_stmt_a.jov              \
 4_1_assignment_stmt_b.jov              \
 4_2_loop_stmt_b.jov                    \
 4_2_loop_stmt_c.jov                    \
 4_2_loop_stmt_d.jov                    \
 4_3_if_stmt_a.jov                      \
 4_6_return_stmt_b.jov                  \
 4_10_abort_stmt_c.jov                  \
 5_1_1_integer-factor.jov               \
 5_1_1_integer-formula.jov

TEST_JOVIAL_Objects  = ${JOVIAL_TESTCODES:.jov=.aterm}
TEST_JOVIAL_Sources  = ${JOVIAL_TESTCODES:.jov=.jov.passed}

TEST_COMPOOL_Objects = ${COMPOOL_TESTCODES:.cpl=.aterm}
TEST_COMPOOL_Sources = ${COMPOOL_TESTCODES:.cpl=.cpl.passed}

PASSING_TEST_Objects = $(TEST_JOVIAL_Objects) $(TEST_COMPOOL_Objects)
#PASSING_TEST_Objects = $(TEST_JOVIAL_Objects)
PASSING_COMPOOL_TEST_Objects = $(TEST_COMPOOL_Objects)

# Go back and build the translator we are using to test Jovial (in case make check
# is run directly in this directory before make has been run from the root of the 
# ROSE directory structure).
../../testParser:
	cd ../..; $(MAKE) testParser

testParser: ../../testParser

$(TEST_JOVIAL_Objects): ../../testParser
	../../testParser $(ROSE_FLAGS) -rose:jovial $(srcdir)/$(@:.aterm=.jov)

$(TEST_COMPOOL_Objects): ../../testParser
	../../testParser $(ROSE_FLAGS) -rose:jovial $(srcdir)/$(@:.aterm=.cpl)

check-compool:
	@echo $(TEST_COMPOOL_Objects)
	@echo $(PASSING_TEST_COMPOOL_Objects)
check-jovial:
	@echo "TEST_JOVIAL_Objects:"
	@echo $(TEST_JOVIAL_Objects)
	@echo "PASSING_TEST_Objects:"
	@echo $(PASSING_TEST_Objects)

clean-local:
	rm -f rose_*.* *.aterm *.dot

check-local:
	@echo "Tests for experimental Jovial frontend."
	@$(MAKE) $(PASSING_TEST_Objects)
	@echo "***********************************************************************************************************************"
	@echo "****** ROSE/tests/nonsmoke/functional/CompileTests/experimental_jovial_tests: make check terminated successfully ******"
	@echo "***********************************************************************************************************************"
