APP_NAME = geometry
APP_NAME_TEST = geometry_test
LIB_NAME = libgeometry

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I src -MP -MMD
CPPFLAGS_TEST = -I thirdparty -I src -MP -MMD
LDFLAGS =
LDLIBS = -lm

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test

APP_PATH_TEST = $(BIN_DIR)/$(APP_NAME_TEST)
APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a

SRC_EXT = c

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

APP_SOURCES_TEST = $(shell find $(TEST_DIR) -name '*.$(SRC_EXT)')
APP_OBJECTS_TEST = $(APP_SOURCES_TEST:$(TEST_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(TEST_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)
DEPS_TEST = $(APP_OBJECTS_TEST:.o=.d) $(LIB_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/%.o: $(SRC_DIR)/$(APP_NAME)/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LDLIBS)

$(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/%.o: $(SRC_DIR)/$(LIB_NAME)/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LDLIBS)

.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(LIB_PATH) $(APP_PATH_TEST)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;

.PHONY: test
test: $(APP_PATH_TEST)

-include $(DEPS_TEST)

$(APP_PATH_TEST): $(APP_OBJECTS_TEST) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS_TEST) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS_TEST) $< -o $@ $(LDLIBS)