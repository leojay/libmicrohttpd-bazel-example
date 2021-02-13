
absl:
	[ -f abseil-cpp-master.tar.xz ] && mv abseil-cpp-master.tar.xz abseil-cpp-master.tar.xz.bak
	wget -O abseil-cpp-master.tar.gz 'https://github.com/abseil/abseil-cpp/archive/master.tar.gz'
	gunzip abseil-cpp-master.tar.gz
	xz -4e abseil-cpp-master.tar
	[ -f abseil-cpp-master.tar.xz.bak ] && sed -i "s/`sha256sum abseil-cpp-master.tar.xz.bak | cut -d' ' -f1`/`sha256sum abseil-cpp-master.tar.xz | cut -d' ' -f1`/" ../WORKSPACE
	[ -f abseil-cpp-master.tar.xz.bak ] && rm abseil-cpp-master.tar.xz.bak


boringssl:
	[ -f chromium-stable-with-bazel.tar.xz ] && mv chromium-stable-with-bazel.tar.xz chromium-stable-with-bazel.tar.xz.bak
	wget 'https://boringssl.googlesource.com/boringssl/+archive/refs/heads/chromium-stable-with-bazel.tar.gz'
	gunzip chromium-stable-with-bazel.tar.gz
	xz -4e chromium-stable-with-bazel.tar
	[ -f chromium-stable-with-bazel.tar.xz.bak ] && sed -i "s/`sha256sum chromium-stable-with-bazel.tar.xz.bak | cut -d' ' -f1`/`sha256sum chromium-stable-with-bazel.tar.xz | cut -d' ' -f1`/" ../WORKSPACE
	[ -f chromium-stable-with-bazel.tar.xz.bak ] && rm chromium-stable-with-bazel.tar.xz.bak
	

tcmalloc:
	[ -f tcmalloc-master.tar.xz ] && mv tcmalloc-master.tar.xz tcmalloc-master.tar.xz.bak
	wget -O tcmalloc-master.tar.gz 'https://github.com/google/tcmalloc/archive/master.tar.gz'
	gunzip tcmalloc-master.tar.gz
	xz -4e tcmalloc-master.tar
	[ -f tcmalloc-master.tar.xz.bak ] && sed -i "s/`sha256sum tcmalloc-master.tar.xz.bak | cut -d' ' -f1`/`sha256sum tcmalloc-master.tar.xz | cut -d' ' -f1`/" ../WORKSPACE
	[ -f tcmalloc-master.tar.xz.bak ] && rm tcmalloc-master.tar.xz.bak


rules_foreign_cc:
	[ -f rules_foreign_cc-master.tar.xz ] && mv rules_foreign_cc-master.tar.xz rules_foreign_cc-master.tar.xz.bak
	wget -O rules_foreign_cc-master.tar.gz 'https://github.com/bazelbuild/rules_foreign_cc/archive/master.tar.gz'
	gunzip rules_foreign_cc-master.tar.gz
	xz -4e rules_foreign_cc-master.tar
	[ -f rules_foreign_cc-master.tar.xz.bak ] && sed -i "s/`sha256sum rules_foreign_cc-master.tar.xz.bak | cut -d' ' -f1`/`sha256sum rules_foreign_cc-master.tar.xz | cut -d' ' -f1`/" ../WORKSPACE
	[ -f rules_foreign_cc-master.tar.xz.bak ] && rm rules_foreign_cc-master.tar.xz.bak

