#ifndef _GPIO_KEYS_H
#define _GPIO_KEYS_H

struct device;

struct gpio_keys_button {
	/* Configuration parameters */
	unsigned int code;	/* input event code (KEY_*, SW_*) */
	int gpio;		/* -1 if this key does not support gpio */
	int active_low;
	const char *desc;
	unsigned int type;	/* input event type (EV_KEY, EV_SW, EV_ABS) */
	int wakeup;		/* configure the button as a wake-up source */
	int debounce_interval;	/* debounce ticks interval in msecs */
	bool can_disable;
	int value;		/* axis value for EV_ABS */
	unsigned int irq;	/* Irq number in case of interrupt keys */
	bool can_reset;		/* key is able to reset system */
	int reset_interval;	/* reset key interval in msec */
};

struct gpio_keys_platform_data {
	struct gpio_keys_button *buttons;
	int nbuttons;
	unsigned int poll_interval;	/* polling interval in msecs -
					   for polling driver only */
	unsigned int rep:1;		/* enable input subsystem auto repeat */
	int (*enable)(struct device *dev);
	void (*disable)(struct device *dev);
	const char *name;		/* input device name */
};


#define RESETKEY_PRESS			0x0001 /* power key is pressed */
#define RESETKEY_RELEASE		0x0002 /* power key is released */
#define RESETKEY_PREPARE_HWREST		0x0003 /* Going to reset whole system by pmic*/

#ifdef CONFIG_KEYBOARD_GPIO
extern int register_resetkey_notifier(struct notifier_block *nb);
extern int unregister_resetkey_notifier(struct notifier_block *nb);
#else
static inline int register_resetkey_notifier(struct notifier_block *nb)
{
	return 0;
}
static inline int unregister_resetkey_notifier(struct notifier_block *nb)
{
	return 0;
}
#endif

#endif
