TEMPLATE = subdirs

SUBDIRS += \
    Application \
    Tests

Tests.depends = Application
