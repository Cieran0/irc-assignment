.PHONY: all bot server

all:
	$(MAKE) bot
	$(MAKE) server

bot:
	$(MAKE) -C bot clean
	$(MAKE) -C bot

server:
	$(MAKE) -C server clean
	$(MAKE) -C server