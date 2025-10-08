(
  cd "$(dirname "$0")" # Ensure compile steps are run within the repository directory
  cmake -B build -DCMAKE_BUILD_TYPE=Debug -S . -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
  cmake --build ./build
)

ctest --output-on-failure --test-dir build