setup() {
    dir="$( cd "$( dirname "$BATS_TEST_FILENAME" )" >/dev/null 2>&1 && pwd )"
    PATH="$dir/../src:$PATH"
    load '../external/bats-support/load'
    load '../external/bats-assert/load'
    valgrind="valgrind --leak-check=full --error-exitcode=1"
}

function no_stderr {
    "$@" 2>/dev/null
}

# Basic usage
# -----------

@test "simprod scenario succeeds" {
    run ./simprod scenario
    assert_success
}

@test "simprod scenario prints an empty JSON scenario" {
    run ./simprod scenario
    assert_line "{"
    assert_line --partial '"timeline": {'
    assert_line --partial '"future-durations": []'
    assert_line --partial '"plants": []'
    assert_line --partial '"zones": []'
    assert_line "}"
}

@test "simprod scenario scenario.json prints the content of scenario.json" {
    ./simprod scenario examples/scenario.json > $BATS_TMPDIR/scenario.json
    diff -s examples/scenario.json $BATS_TMPDIR/scenario.json
}

# Memory management
# -----------------

@test "simprod scenario manages its memory correctly" {
    run $valgrind ./simprod scenario
    assert_success
}

@test "simprod scenario scenario.json manages its memory correctly" {
    run $valgrind ./simprod scenario examples/scenario.json
    assert_success
}

# With option -t|--to
# -------------------

@test "simprod scenario -t json prints an empty JSON scenario" {
    run ./simprod scenario -t json
    assert_line "{"
    assert_line --partial '"timeline": {'
    assert_line --partial '"future-durations": []'
    assert_line --partial '"plants": []'
    assert_line --partial '"zones": []'
    assert_line "}"
}

@test "simprod scenario -t dot prints an empty DOT digraph" {
    run ./simprod scenario -t dot
    assert_line --partial 'digraph {'
    assert_line --partial 'timeline'
    assert_line --partial 'num-future-timesteps: 0'
    assert_line --partial 'future-durations: []'
    assert_line --partial '}'
}

@test "simprod scenario scenario_timeline.dot -t dot prints its DOT digraph" {
    run ./simprod scenario examples/scenario_timeline.json -t dot
    assert_line --partial 'digraph {'
    assert_line --partial 'timeline'
    assert_line --partial 'num-future-timesteps: 3'
    assert_line --partial 'future-durations: [10, 30, 60]'
    assert_line --partial '}'
}

@test "simprod scenario scenario_zone.dot -t dot prints its DOT digraph" {
    run ./simprod scenario examples/scenario_zone.json -t dot
    assert_line --partial 'digraph {'
    assert_line --partial 'timeline'
    assert_line --partial 'num-future-timesteps: 3'
    assert_line --partial 'future-durations: [10, 30, 60]'
    assert_line --partial 'Zone Z'
    assert_line --partial 'expected-demands: [1.5, 2.5, 3.5]'
    assert_line --partial '}'
}

@test "simprod scenario scenario_plant.dot -t dot prints its DOT digraph" {
    run ./simprod scenario examples/scenario_plant.json -t dot
    assert_line --partial 'digraph {'
    assert_line --partial 'timeline'
    assert_line --partial 'num-future-timesteps: 3'
    assert_line --partial 'future-durations: [10, 30, 60]'
    assert_line --partial 'Plant P'
    assert_line --partial 'min-powers: [1.5, 2.5, 3.5]'
    assert_line --partial 'max-powers: [4.5, 5.5, 6.5]'
    assert_line --partial 'Zone Z'
    assert_line --partial 'expected-demands: [1, 2, 3]'
    assert_line --partial 'odiamond'
    assert_line --partial '"plant_P" -> "zone_Z"'
    assert_line --partial '}'
}

@test "simprod scenario scenario_link.dot -t dot prints its DOT digraph" {
    run ./simprod scenario examples/scenario_link.json -t dot
    assert_line --partial 'digraph {'
    assert_line --partial 'timeline'
    assert_line --partial 'num-future-timesteps: 3'
    assert_line --partial 'future-durations: [10, 30, 60]'
    assert_line --partial 'Link L_Z1-&gt;Z2'
    assert_line --partial 'Zone Z1'
    assert_line --partial 'expected-demands: [1, 2, 3]'
    assert_line --partial 'Zone Z2'
    assert_line --partial 'expected-demands: [4, 5, 6]'
    assert_line --partial 'zone_Z1" -> "link_L_Z1->Z2"'
    assert_line --partial 'link_L_Z1->Z2" -> "zone_Z2"'
}

# With wrong argument
# -------------------

@test "simprod scenario with too many arguments fails" {
    run ./simprod scenario a b c d
    assert_failure
    assert_line --partial 'Too many arguments'
}

@test "simprod scenario with invalid JSON filepath fails" {
    run ./simprod scenario non-existing.json
    assert_failure
    assert_line --partial 'No such file'
}
