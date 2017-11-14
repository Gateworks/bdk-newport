-- ***********************license start***********************************
-- Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
-- reserved.
--
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions are
-- met:
--
--   * Redistributions of source code must retain the above copyright
--     notice, this list of conditions and the following disclaimer.
--
--   * Redistributions in binary form must reproduce the above
--     copyright notice, this list of conditions and the following
--     disclaimer in the documentation and/or other materials provided
--     with the distribution.
--
--   * Neither the name of Cavium Inc. nor the names of
--     its contributors may be used to endorse or promote products
--     derived from this software without specific prior written
--     permission.
--
-- This Software, including technical data, may be subject to U.S. export
-- control laws, including the U.S. Export Administration Act and its
-- associated regulations, and may be subject to export or import
-- regulations in other countries.
--
-- TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
-- AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
-- WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
-- TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
-- REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
-- DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
-- OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
-- PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
-- QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
-- ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
-- **********************license end**************************************

--- Module for logging data in a uniform way with debug levels.
-- 1. Create a new logger object by calling logging.new().
-- 2. Then use logger methods to send output.
-- 3. Only messages below the log level are displayed.
--
-- * Written by Chad Reese
-- * Copyright (C) 2010-2017 Cavium Inc.
--
-- @alias logging
require("utils")

local logging = {}
--- Logs all information including debug
logging.DEBUG = 3
--- Logs informational, warnings, errors, and fatal
logging.INFO = 2
--- Logs warnings, errors, and fatal. This is the default.
logging.WARN = 1

---
-- Internal function that actually writes the message
--
local function log_write(logger, level, arg1, ...)
    printf("%s[%s]: ", level, logger.unit)
    if type(arg1) == "string" then
        printf(arg1, ...)
    else
        pprint(arg1)
    end
end

--- @class logger
-- Object returned by new()

---
-- Called to log DEBUG messages
-- @function logger:debug
-- @param format printf style format string
-- @param ... Arguments to format string
--
local function log_debug(logger, arg1, ...)
    if logger.level >= logging.DEBUG then
        log_write(logger, "DEBUG", arg1, ...)
    end
end

---
-- Called to log INFO messages
-- @function logger:info
-- @param format printf style format string
-- @param ... Arguments to format string
--
local function log_info(logger, arg1, ...)
    if logger.level >= logging.INFO then
        log_write(logger, "INFO", arg1, ...)
    end
end

---
-- Called to log WARN messages
-- @function logger:warn
-- @param format printf style format string
-- @param ... Arguments to format string
--
local function log_warn(logger, arg1, ...)
    log_write(logger, "WARN", arg1, ...)
end

---
-- Called to log ERROR messages
-- @function logger:error
-- @param format printf style format string
-- @param ... Arguments to format string
--
local function log_error(logger, arg1, ...)
    log_write(logger, "ERROR", arg1, ...)
end

---
-- Called to log FATAL messages
-- @function logger:fatal
-- @param format printf style format string
-- @param ... Arguments to format string
--
local function log_fatal(logger, arg1, ...)
    log_write(logger, "FATAL", arg1, ...)
    error("FATAL message logged")
end

---
-- Create a new logger for a unit. If level isn't specified it defaults
-- to logging.WARN.
-- @param unit String name for object/unit that messages are for.
-- @param level Level of debug output to log
-- @return New "logger" object
--
function logging.new(unit, level)
    local logger = {}
    logger.unit = unit
    logger.level = level or logging.WARN
    logger.debug = log_debug
    logger.info = log_info
    logger.warn = log_warn
    logger.error = log_error
    logger.fatal = log_fatal
    return logger
end

return logging
