/**
 * esp32_manager_storage.h
 * 
 * (C) 2019 - Pablo Bacho <pablo@pablobacho.com>
 * This code is licensed under the MIT License.
 */

#ifndef _ESP32_MANAGER_STORAGE_H_
#define _ESP32_MANAGER_STORAGE_H_

#include <string.h>
#include <math.h>

#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ESP32_MANAGER_NAMESPACES_SIZE  10     /*!< Maximum number of namespaces that can be registered */
  
#define ESP32_MANAGER_ATTR_READ         0b00000001  /*!< READ flag */
#define ESP32_MANAGER_ATTR_WRITE        0b00000010  /*!< WRITE flag */
#define ESP32_MANAGER_ATTR_READWRITE    0b00000011  /*!< READ & WRITE attributes. Meant for readability of the code because of both being commonly used together. */

/**
 * Settings type.
 */
typedef enum {i8=0, u8=1, i16=2, u16=3, i32=4, u32=5, i64=6, u64=7, flt=8, dbl=9,
        multiple_choice=20, single_choice=21,
        text=40, password=41,
        blob=60, image=61} esp32_manager_type_t;

/**
 * Settings entry
 */
typedef struct {
    const char * key;               /*!< unique key to identify the entry */
    const char * friendly;          /*!< Friendly or human-readable name */
    esp32_manager_type_t type;      /*!< type */
    void * value;                   /*!< pointer to the variable where the value of the setting is stored */
    void * default_value;           /*!< Default value */
    uint32_t attributes;            /*!< attributes */
} esp32_manager_entry_t;

/**
 * Namespace handle.
 */
typedef struct {
    const char * key;       /*!< Namespace key */
    const char * friendly;  /*!< Namespace friendly or human-readable name */
    esp32_manager_entry_t ** entries;
    uint8_t size;
    nvs_handle nvs_handle;  /*!< NVS handle for this namespace */
} esp32_manager_namespace_t;

/**
 * Array to store namespace objects
 */
extern esp32_manager_namespace_t * esp32_manager_namespaces[ESP32_MANAGER_NAMESPACES_SIZE];

/**
 * @brief   Initialize esp32_manager
 * 
 * This function should be called only once.
 * 
 * @return  ESP_OK: success
 *          ESP_FAIL: error opening NVS
 *          ESP_ERR_NVS_PART_NOT_FOUND: NVS partition not found
 */
esp_err_t esp32_manager_storage_init();

/**
 * @brief   Register namespace with esp32_manager
 * 
 * @param   key key of the namespace
 * @param   friendly Friendly or human-readable name of the namespace
 * @return  handle to the namespace registered or null for error
 */
esp_err_t esp32_manager_register_namespace(esp32_manager_namespace_t * namespace);

/**
 * @brief   Register esp32 entry
 * 
 * @param   namespace pointer to the namespace the entry belongs to
 * @param   entry entry to be registered
 * @return  ESP_OK success
 *          ESP_ERR_NO_MEM no empty slots available for this entry
 *          ESP_ERR_INVALID_ARG namespace or entry pointers are not valid
 */
esp_err_t esp32_manager_register_entry(esp32_manager_namespace_t * namespace, esp32_manager_entry_t * entry);

/**
 * @brief   Commits all esp32 under a namespace to NVS for permanent storage
 * 
 * @param   namespace pointer to the namespace
 * @return  ESP_OK success
 *          ESP_FAIL error
 *          ESP_ERR_INVALID_ARG invalid handle
 */
esp_err_t esp32_manager_commit_to_nvs(esp32_manager_namespace_t * namespace);

/**
 * @brief   Read all esp32 under a namespace from NVS
 * 
 * @param   namespace pointer to the namespace
 * @return  ESP_OK success
 *          ESP_FAIL error
 *          ESP_ERR_INVALID_ARG invalid handle
 */
esp_err_t esp32_manager_read_from_nvs(esp32_manager_namespace_t * namespace);

/**
 * @brief   Convert a setting value to string
 * 
 * @param   dest Destination buffer
 * @param   entry pointer to the esp32 entry
 * @return  ESP_OK success
 *          ESP_FAIL error
 *          ESP_ERR_INVALID_ARG for invalid arguments
 */
esp_err_t esp32_manager_entry_to_string(char * dest, esp32_manager_entry_t * entry);

#ifdef __cplusplus
}
#endif

#endif // _ESP32_MANAGER_ENTRIES_H_