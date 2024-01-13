/*
 * Support for Flydigi Vader 3 via Bluetooth (hardware doesn't support FF in that mode).
 *
 * Learning References (tutorials/blogs):
 * https://www.nirenjan.com/2020/linux-hid-driver/
 *
 * Project References:
 * https://github.com/atar-axis/vader3
 *
 * See also:
 * https://github.com/atar-axis/xpadneo/pull/451 if
 */

#include <linux/delay.h>
#include <linux/hid.h>
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
  // return -1;

  // This uses the AUTO / underlying driver defaults - xpadneo has
  // an area where they use STATIC and redefine their own map of codes
  // to generated values - I wonder which is most appropriate to map at?
  // We can do it here, against codes (which could collide with a name brand controller),
  // or we can fiddle bits in the raw area and let them bubble up, or we can
  // remap them in the event handler (this seems easiest to get the hid-generic values out of)
  return 0;
}

static int vader3_input_configured(struct hid_device *dev,
                                   struct hid_input *input)
{
    struct input_dev * input_dev = input->input;
    int i;
    int max_btn = 16;
    int abs_min = -128;
    int abs_max = 127;
    int deadzone = (int) ((abs_max - abs_min) * 0.1);

    hid_set_drvdata(dev, input_dev);

    // Define features
    set_bit(EV_KEY, input_dev->evbit);
    set_bit(EV_ABS, input_dev->evbit);

    // If we want to initialize buttons under the first 16, we can, but it
    // would violate the Xbox spec, and xpadneo devs recommend we stick to trigger happy range.
    // set_bit(BTN_C, input_dev->keybit);

    // So, we'll just initialize the trigger happy range
    for (i = 0; i < max_btn; i++) {
        set_bit(BTN_TRIGGER_HAPPY1 + i, input_dev->keybit);
    }

    // Define stick capabilities
    set_bit(ABS_X, input_dev->absbit);
    set_bit(ABS_Y, input_dev->absbit);
    set_bit(ABS_Z, input_dev->absbit);
    set_bit(ABS_RZ, input_dev->absbit);

    // d-pad
    set_bit(ABS_HAT0Y, input_dev->keybit);
    set_bit(ABS_HAT0X, input_dev->keybit);

    // Define stick ranges
    input_set_abs_params(input_dev, ABS_X, abs_min, abs_max, 32, deadzone);
    input_set_abs_params(input_dev, ABS_Y, abs_min, abs_max, 32, deadzone);
    input_set_abs_params(input_dev, ABS_Z, abs_min, abs_max, 32, deadzone);
    input_set_abs_params(input_dev, ABS_RZ, abs_min, abs_max, 32, deadzone);

    // d-pad
    /* input_set_abs_params(input_dev, ABS_HAT0Y, -1, 1, 32, 0); */
    /* input_set_abs_params(input_dev, ABS_HAT0X, -1, 1, 32, 0); */

    return 0;
}

// I guess we can log/report on exact raw events if we want, but if we don't
// act on it, I think it passes through to the event function.
static int vader3_raw_event(struct hid_device *dev,
                            struct hid_report *report, u8 *data, int len)
{
  // struct input_dev *input_dev = hid_get_drvdata(dev);

  /* hid_info(input_dev, "raw_event data 0: %d\n", data[0]); */
  /* hid_info(input_dev, "raw_event data 1: %d\n", data[1]); */
  /* hid_info(input_dev, "raw_event data 2: %d\n", data[2]); */
  /* hid_info(input_dev, "raw_event data 3: %d\n", data[3]); */
  /* hid_info(input_dev, "raw_event data 4: %d\n", data[4]); */
  /* hid_info(input_dev, "raw_event data 5: %d\n", data[5]); */
  /* hid_info(input_dev, "raw_event data 6: %d\n", data[6]); */
  /* hid_info(input_dev, "raw_event data 7: %d\n", data[7]); */
  /* hid_info(input_dev, "raw_event data 8: %d\n", data[8]); */
  /* hid_info(input_dev, "raw_event data 9: %d\n", data[9]); */
  /* hid_info(input_dev, "raw_event data 10: %d\n", data[10]); */
  /* hid_info(input_dev, "raw_event data 11: %d\n", data[11]); */
  /* hid_info(input_dev, "raw_event data 12: %d\n", data[12]); */
  /* hid_info(input_dev, "raw_event data 13: %d\n", data[13]); */
  /* hid_info(input_dev, "raw_event data 14: %d\n", data[14]); */
  /* hid_info(input_dev, "raw_event data 15: %d\n", data[15]); */
  /* hid_info(input_dev, "raw_event data 16: %d\n", data[16]); */
  /* hid_info(input_dev, "raw_event data 17: %d\n", data[17]); */

  // Fix the rightmost back button, the others are 8/16/32, and 64 makes it recognized
  // If we don't do this, it actually won't be detected by qjoypad
  if (data[11] == 4)
    {
      data[11] = 64;
    }

  // C-button reports as BTN_0
  /* if (data[11] == 1) */
  /*   { */
  /*     input_report_key(input_dev, BTN_C, 1); */
  /*   } */

  // Z-button reports as Return
  /* if (data[11] == 2) */
  /*   { */
  /*     data[11] = 0; */
  /*     data[12] = 1; */
  /*   } */

  /* input_sync(input_dev); */

  return 0;

  // Sample from the tutorial, auto-mapping a bunch of stuff

    /* struct input_dev *input_dev = hid_get_drvdata(dev); */
    /* int ret = 0; */
    /* int btn; */
    /* int idx; */
    /* int num_buttons = 16; */

    /* // Samples of how we can overwrite this to anything we want. */
    /* input_report_abs(input_dev, ABS_Z, data[4]); */
    /* input_report_abs(input_dev, ABS_RX, data[5]); */
    /* input_report_abs(input_dev, ABS_RY, data[6]); */
    /* input_report_abs(input_dev, ABS_MISC, data[7]); */

    /* /\* ... *\/ */
    /* for (int i = 0; i < num_buttons; i++) */
    /*   { */
    /*     idx = 8 + (i / BITS_PER_BYTE); */
    /*     btn = !!(data[idx] & (1 << (i % BITS_PER_BYTE))); */
    /*     input_report_key(input_dev, BTN_TRIGGER_HAPPY + i, btn); */
    /*   } */

    /* input_sync(input_dev); */
    /* return ret; */
}

static int vader3_event(struct hid_device *dev, struct hid_field *field,
			 struct hid_usage *usage, __s32 value)
{
  struct input_dev *input_dev = hid_get_drvdata(dev);

  // hid_info(input_dev, "type: %d\n", usage->type);

  // d-pad is all messed up
  // up/down:
  //   type 3 (EV_ABS), code 17 (ABS_HAT0Y), value -1 (up), 1 (down), and 0 unpressed
  // left/right:
  //   type 3 (EV_ABS), code 16 (ABS_HAT0X), value -1 (left), 1 (right), and 0 unpressed
  // Some users complain about multiple directions inputs registering at once, I bet
  // we could track that state here and ensure it's not possible to press left and right
  // at the same time

  if (usage->type == EV_ABS)
    {
      switch (usage->code)
        {
        case ABS_HAT0X: // all d-pad comes through as this
          switch (value)
            {
            case 1: // up
              input_report_abs(input_dev, ABS_HAT0Y, -1);
              break;

            case 5: // down
              input_report_abs(input_dev, ABS_HAT0Y, 1);
              break;

            case 7: // left
              input_report_abs(input_dev, ABS_HAT0X, -1);
              break;

            case 3: // right
              input_report_abs(input_dev, ABS_HAT0X, 1);
              break;

            case 2: // up-right
              input_report_abs(input_dev, ABS_HAT0Y, -1);
              input_report_abs(input_dev, ABS_HAT0X, 1);
              break;

            case 4: // bottom-right
              input_report_abs(input_dev, ABS_HAT0Y, 1);
              input_report_abs(input_dev, ABS_HAT0X, 1);
              break;

            case 6: // bottom-left
              input_report_abs(input_dev, ABS_HAT0Y, 1);
              input_report_abs(input_dev, ABS_HAT0X, -1);
              break;

            case 8: // up-left
              input_report_abs(input_dev, ABS_HAT0Y, -1);
              input_report_abs(input_dev, ABS_HAT0X, -1);
              break;

            case 0: // no direction
              input_report_abs(input_dev, ABS_HAT0X, 0);
              input_report_abs(input_dev, ABS_HAT0Y, 0);
              break;

            default:
              hid_info(input_dev, "Unknown d-pad direction: %d\n", value);
              // input_report_abs(input_dev, usage->code, value);
              break;

            }
          break;

        default:
          // If we want Linux Gamepad Specification, we can multiply the value here to 32k
          // It seems to show up as that in jstest already?
          input_report_abs(input_dev, usage->code, value);
          break;
        }
      return 1;
    }

  if (usage->type == EV_KEY)
    {
      // Special remapping to make it work correctly and not show weird events out of joy range
      switch (usage->code)
        {
        case BTN_0: // C-Button
          input_report_key(input_dev, BTN_TRIGGER_HAPPY1, value);
          // input_report_key(input_dev, BTN_C, value);
          break;
        case KEY_ENTER: // Z-Button
          input_report_key(input_dev, BTN_TRIGGER_HAPPY2, value);
          break;
        case KEY_CHANNELUP: // Leftmost back button
          input_report_key(input_dev, BTN_TRIGGER_HAPPY3, value);
          break;
        case KEY_TV: // Second leftmost back button
          input_report_key(input_dev, BTN_TRIGGER_HAPPY4, value);
          break;
        case KEY_CHANNELDOWN: // Second rightmost back button
          input_report_key(input_dev, BTN_TRIGGER_HAPPY5, value);
          break;
        case KEY_PROGRAM: // Rightmost back button
        case KEY_EJECTCD: // Original without our raw re-map - that shows up in evtest but NOT qjoypad
          input_report_key(input_dev, BTN_TRIGGER_HAPPY6, value);
          break;
        case KEY_CAMERA: // Circle button under joysticks
          input_report_key(input_dev, BTN_TRIGGER_HAPPY7, value);
          break;
        case KEY_RED: // Home button under joysticks
          input_report_key(input_dev, BTN_TRIGGER_HAPPY8, value);
          break;
        default: // Anything else, just pass through (why do their usage codes work?)
          input_report_key(input_dev, usage->code, value);
          break;
        }

      return 1;
    }

  return 0;
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
  .event = vader3_event,
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
