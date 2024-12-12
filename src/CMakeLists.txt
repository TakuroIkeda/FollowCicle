add_library(test
  SHARED
    simulate.c
  )
# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(test
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
