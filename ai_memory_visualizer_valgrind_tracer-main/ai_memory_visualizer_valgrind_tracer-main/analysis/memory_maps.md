# Memory Maps — AI Memory Visualizer

stack_example: recursion and stack frames
[enter] depth=0
  &local_int=0x7ffc39787ad4  p_local=0x7ffc39787ad4  local_int=100
  local_buf=0x7ffc39787ae0  local_buf[0]=A
  &marker=0x7ffc39787b24  marker=0
[enter] depth=1
  &local_int=0x7ffc39787aa4  p_local=0x7ffc39787aa4  local_int=101
  local_buf=0x7ffc39787ab0  local_buf[0]=B
  &marker=0x7ffc39787af4  marker=10
[enter] depth=2
  &local_int=0x7ffc39787a74  p_local=0x7ffc39787a74  local_int=102
  local_buf=0x7ffc39787a80  local_buf[0]=C
  &marker=0x7ffc39787ac4  marker=20
[enter] depth=3
  &local_int=0x7ffc39787a44  p_local=0x7ffc39787a44  local_int=103
  local_buf=0x7ffc39787a50  local_buf[0]=D
  &marker=0x7ffc39787a94  marker=30
[exit] depth=3
  &local_int=0x7ffc39787a44  p_local=0x7ffc39787a44  local_int=103
  local_buf=0x7ffc39787a50  local_buf[0]=D
  &marker=0x7ffc39787a94  marker=30
[exit] depth=2
  &local_int=0x7ffc39787a74  p_local=0x7ffc39787a74  local_int=102
  local_buf=0x7ffc39787a80  local_buf[0]=C
  &marker=0x7ffc39787ac4  marker=20
[exit] depth=1
  &local_int=0x7ffc39787aa4  p_local=0x7ffc39787aa4  local_int=101
  local_buf=0x7ffc39787ab0  local_buf[0]=B
  &marker=0x7ffc39787af4  marker=10
[exit] depth=0
  &local_int=0x7ffc39787ad4  p_local=0x7ffc39787ad4  local_int=100
  local_buf=0x7ffc39787ae0  local_buf[0]=A
  &marker=0x7ffc39787b24  marker=0
