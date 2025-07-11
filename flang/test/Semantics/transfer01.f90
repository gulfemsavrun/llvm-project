! RUN: %python %S/test_errors.py %s %flang_fc1 -pedantic
! Check errors in TRANSFER()

subroutine subr(o)
  integer, intent(in), optional :: o
  type empty
  end type
  type(empty) :: empty1(1)
  type hasdescriptor
    real, allocatable :: allocatable
  end type
  type(hasdescriptor) hasDesc
  real :: empty2(0)
  character(0) :: empty3(1)
  integer, pointer :: source(:)
  integer, allocatable :: ia
  integer, pointer :: ip
  !ERROR: Element size of MOLD= array may not be zero when SOURCE= is not empty
  print *, transfer(1., empty1)
  print *, transfer(1., empty2) ! ok
  !ERROR: Element size of MOLD= array may not be zero when SOURCE= is not empty
  print *, transfer(1., empty3)
  !WARNING: Element size of MOLD= array may not be zero unless SOURCE= is empty [-Wvoid-mold]
  print *, transfer(source, empty1)
  print *, transfer(source, empty2) ! ok
  !WARNING: Element size of MOLD= array may not be zero unless SOURCE= is empty [-Wvoid-mold]
  print *, transfer(source, empty3)
  !ERROR: SIZE= argument may not be the optional dummy argument 'o'
  print *, transfer(1., empty2, size=o)
  !WARNING: SIZE= argument that is allocatable or pointer must be present at execution; parenthesize to silence this warning [-Wtransfer-size-presence]
  print *, transfer(1., empty2, size=ia)
  !WARNING: SIZE= argument that is allocatable or pointer must be present at execution; parenthesize to silence this warning [-Wtransfer-size-presence]
  print *, transfer(1., empty2, size=ip)
  !WARNING: Source of TRANSFER contains allocatable or pointer component %allocatable [-Wpointer-component-transfer-arg]
  print *, transfer(hasDesc, 1)
end
