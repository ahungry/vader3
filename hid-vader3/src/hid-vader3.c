/*
 * Support for Flydigi Vader 3 via Bluetooth (hardware doesn't support FF in that mode).
 *
 * Learning References (tutorials/blogs):
 * https://www.nirenjan.com/2020/linux-hid-driver/
 *
 * Project References:
 * https://github.com/atar-axis/vader3
 */

#include <linux/delay.h>
// #include <linux/hid.h>
#include <linux/module.h>

#include "vader3.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matthew Carter <m@ahungry.com>");
MODULE_DESCRIPTION("Linux kernel driver for Flydigi Vader 3 via Bluetooth");
MODULE_VERSION(VADER3_VERSION);

#define VENDOR_FLYDIGI 0xD7D7
#define DEV_VADER3 0x0041

static int vader3_input_mapping(struct hid_device *dev,
                                struct hid_input *input,
                                struct hid_field *field,
                                struct hid_usage *usage,
                                unsigned long **bit,
                                int *max)
{
  /*
     * We are reporting the events in vader3_raw_event.
     * Skip the hid-input processing.
     */
    return -1;
}

static int vader3_input_configured(struct hid_device *dev,
                                   struct hid_input *input)
{
    struct input_dev * input_dev = input->input;
    int i;
    int max_btn = 16;
    int max_stick = 127;

    hid_set_drvdata(dev, input_dev);

    set_bit(EV_KEY, input_dev->evbit);
    set_bit(EV_ABS, input_dev->evbit);

    // ...

    for (i = 0; i < max_btn; i++) {
        set_bit(BTN_TRIGGER_HAPPY1 + i, input_dev->keybit);
    }

    set_bit(ABS_X, input_dev->absbit);
    set_bit(ABS_Y, input_dev->absbit);
    set_bit(ABS_Z, input_dev->absbit);
    /* ... */

    input_set_abs_params(input_dev, ABS_X, 0, max_stick, max_stick >> 8, max_stick >> 4);
    input_set_abs_params(input_dev, ABS_Y, 0, max_stick, max_stick >> 8, max_stick >> 4);
    input_set_abs_params(input_dev, ABS_Z, 0, 255, 0, 15);
    /* ... */

    return 0;
}

static int vader3_raw_event(struct hid_device *dev,
                            struct hid_report *report, u8 *data, int len)
{
    struct input_dev *input_dev = hid_get_drvdata(dev);
    int ret = 0;
    int btn;
    int idx;
    int num_buttons = 16;

    /* ... */
    input_report_abs(input_dev, ABS_Z, data[4]);
    input_report_abs(input_dev, ABS_RX, data[5]);
    input_report_abs(input_dev, ABS_RY, data[6]);
    input_report_abs(input_dev, ABS_MISC, data[7]);

    /* ... */
    for (int i = 0; i < num_buttons; i++)
      {
        idx = 8 + (i / BITS_PER_BYTE);
        btn = !!(data[idx] & (1 << (i % BITS_PER_BYTE)));
        input_report_key(input_dev, BTN_TRIGGER_HAPPY + i, btn);
      }

    input_sync(input_dev);
    return ret;
}

static const struct hid_device_id vader3_devices[] = {
  { HID_BLUETOOTH_DEVICE(VENDOR_FLYDIGI, DEV_VADER3) },
  {}
};

MODULE_DEVICE_TABLE(hid, vader3_devices);

static struct hid_driver vader3_driver = {
  .name = "vader3",
  .id_table = vader3_devices,
  .input_mapping = vader3_input_mapping,
  .input_configured = vader3_input_configured,
  .raw_event = vader3_raw_event,
};

// module_hid_driver(vader3_driver);
static int __init vader3_init(void)
{
 	pr_info("loaded hid-vader3 %s\n", VADER3_VERSION);
	dbg_hid("vader3:%s\n", __func__);

  int ret = hid_register_driver(&vader3_driver);

	return ret;
}

static void __exit vader3_exit(void)
{
 	dbg_hid("vader3:%s\n", __func__);
	hid_unregister_driver(&vader3_driver);
}

module_init(vader3_init);
module_exit(vader3_exit);
