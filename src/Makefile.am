DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)

if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) $(AM_CPPFLAGS) $(CPPFLAGS) -D__STDC_LIMIT_MACROS"
endif

ALISINABIT_CONFIG_INCLUDES=-I$(builddir)/config
ALISINABIT_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

ALISINABIT_INCLUDES += -I$(srcdir)/secp256k1/include
ALISINABIT_INCLUDES += -I$(srcdir)/univalue/include

LIBALISINABIT_SERVER=libalisinabit_server.a
LIBALISINABIT_WALLET=libalisinabit_wallet.a
LIBALISINABIT_COMMON=libalisinabit_common.a
LIBALISINABIT_CLI=libalisinabit_cli.a
LIBALISINABIT_UTIL=libalisinabit_util.a
LIBALISINABIT_CRYPTO=crypto/libalisinabit_crypto.a
LIBALISINABITQT=qt/libalisinabitqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la
LIBUNIVALUE=univalue/libunivalue.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
  
$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libalisinabit_crypto.a \
  libalisinabit_util.a \
  libalisinabit_common.a \
  libalisinabit_server.a \
  libalisinabit_cli.a
if ENABLE_WALLET
ALISINABIT_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libalisinabit_wallet.a
endif
if ENABLE_ZMQ
EXTRA_LIBRARIES += libalisinabit_zmq.a
endif

if BUILD_ALISINABIT_LIBS
lib_LTLIBRARIES = libalisinabitconsensus.la
LIBALISINABIT_CONSENSUS=libalisinabitconsensus.la
else
LIBALISINABIT_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_ALISINABITD
  bin_PROGRAMS += alisinabitd
endif

if BUILD_ALISINABIT_UTILS
  bin_PROGRAMS += alisinabit-cli alisinabit-tx
if ENABLE_WALLET
  bin_PROGRAMS += wallet-utility
endif
endif

.PHONY: FORCE check-symbols check-security
# alisinabit core #
ALISINABIT_CORE_H = \
  addressindex.h \
  spentindex.h \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  core_io.h \
  core_memusage.h \
  hash.h \
  httprpc.h \
  httpserver.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  prevector.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  reverselock.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  versionbits.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libalisinabit_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between alisinabitd and alisinabit-qt
libalisinabit_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libalisinabit_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libalisinabit_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(ALISINABIT_CORE_H)

if ENABLE_ZMQ
LIBALISINABIT_ZMQ=libalisinabit_zmq.a

libalisinabit_zmq_a_CPPFLAGS = $(ALISINABIT_INCLUDES) $(ZMQ_CFLAGS)
libalisinabit_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libalisinabit_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between alisinabitd and alisinabit-qt, but only linked
# when wallet enabled
libalisinabit_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_INCLUDES)
libalisinabit_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libalisinabit_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  policy/rbf.cpp \
  $(ALISINABIT_CORE_H)

# crypto primitives library
crypto_libalisinabit_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_CONFIG_INCLUDES)
crypto_libalisinabit_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libalisinabit_crypto_a_SOURCES = \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# common: shared between alisinabitd, and alisinabit-qt and non-server tools
libalisinabit_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_INCLUDES)
libalisinabit_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libalisinabit_common_a_SOURCES = \
  amount.cpp \
  arith_uint256.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  consensus/merkle.cpp \
  core_read.cpp \
  core_write.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  protocol.cpp \
  pubkey.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(ALISINABIT_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libalisinabit_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_INCLUDES)
libalisinabit_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libalisinabit_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(ALISINABIT_CORE_H)

if GLIBC_BACK_COMPAT
libalisinabit_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between alisinabit-cli and alisinabit-qt
libalisinabit_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_INCLUDES)
libalisinabit_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libalisinabit_cli_a_SOURCES = \
  rpcclient.cpp \
  $(ALISINABIT_CORE_H)

nodist_libalisinabit_util_a_SOURCES = $(srcdir)/obj/build.h
#

# alisinabitd binary #
alisinabitd_SOURCES = alisinabitd.cpp
alisinabitd_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_INCLUDES)
alisinabitd_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
alisinabitd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
alisinabitd_SOURCES += alisinabitd-res.rc
endif

alisinabitd_LDADD = \
  $(LIBALISINABIT_SERVER) \
  $(LIBALISINABIT_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBALISINABIT_UTIL) \
  $(LIBALISINABIT_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_ZMQ
alisinabitd_LDADD += $(LIBALISINABIT_ZMQ) $(ZMQ_LIBS)
endif

if ENABLE_WALLET
alisinabitd_LDADD += libalisinabit_wallet.a
endif

alisinabitd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

# alisinabit-cli binary #
alisinabit_cli_SOURCES = alisinabit-cli.cpp
alisinabit_cli_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_INCLUDES) $(EVENT_CFLAGS)
alisinabit_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
alisinabit_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

# wallet-utility binary #
if ENABLE_WALLET
wallet_utility_SOURCES = wallet-utility.cpp
wallet_utility_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_INCLUDES) $(EVENT_CFLAG)
wallet_utility_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
wallet_utility_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)
endif

if TARGET_WINDOWS
alisinabit_cli_SOURCES += alisinabit-cli-res.rc
endif

alisinabit_cli_LDADD = \
  $(LIBALISINABIT_CLI) \
  $(LIBUNIVALUE) \
  $(LIBALISINABIT_UTIL)

alisinabit_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
if ENABLE_WALLET
wallet_utility_LDADD = libalisinabit_wallet.a $(LIBALISINABIT_COMMON) $(LIBALISINABIT_CRYPTO) $(LIBSECP256K1) $(LIBALISINABIT_UTIL) $(BOOST_LIBS) $(BDB_LIBS) $(CRYPTO_LIBS)
endif

#

# alisinabit-tx binary #
alisinabit_tx_SOURCES = alisinabit-tx.cpp
alisinabit_tx_CPPFLAGS = $(AM_CPPFLAGS) $(ALISINABIT_INCLUDES)
alisinabit_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
alisinabit_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
alisinabit_tx_SOURCES += alisinabit-tx-res.rc
endif

alisinabit_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBALISINABIT_COMMON) \
  $(LIBALISINABIT_UTIL) \
  $(LIBALISINABIT_CRYPTO) \
  $(LIBSECP256K1)

alisinabit_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# alisinabitconsensus library #
if BUILD_ALISINABIT_LIBS
include_HEADERS = script/alisinabitconsensus.h
libalisinabitconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/alisinabitconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libalisinabitconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libalisinabitconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libalisinabitconsensus_la_LIBADD = $(LIBSECP256K1)
libalisinabitconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_ALISINABIT_INTERNAL
libalisinabitconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a
CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
