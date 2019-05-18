function(cppcheck_targets)

	cmake_parse_arguments(PARSED_ARGS # prefix of output variables
	                      "" # list of names of the boolean arguments
	                      "" # list of names of mono-valued arguments
	                      "TARGETS;SUPPRESS;INCLUDE" # multi-valued arguments
	                      ${ARGN}
	                      )

	if(NOT PARSED_ARGS_TARGETS)
		message(FATAL_ERROR "You must provide at least one targets")
	endif(NOT PARSED_ARGS_TARGETS)

	set (targets "")
	foreach(t ${PARSED_ARGS_TARGETS})
		get_target_property(src ${t} SOURCES)
		list(APPEND targets "${src}")
	endforeach(t)

	set(suppressions "")
	foreach(s ${PARSED_ARGS_SUPPRESS})
		list(APPEND suppressions "--suppress=${s}")
	endforeach(s)

	set(target_command
	    COMMAND cppcheck
	    --enable=all
	    --std=c++11
	    --template=gcc
	    --inconclusive
	    --suppress=missingIncludeSystem
	    ${suppressions}
	    --quiet
	    --error-exitcode=1
	    -I ${PARSED_ARGS_INCLUDE}
	    ${targets}
	    )

	set_property(GLOBAL APPEND PROPERTY memedar_cppcheck_property ${target_command})

endfunction(cppcheck_targets)
