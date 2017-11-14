#!/usr/bin/perl
#!/usr/bin/perl -w
# ***********************license start***********************************
# Copyright (c) 2003-2016  Cavium Inc. (support@cavium.com). All rights
# reserved.
#
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#   * Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#
#   * Neither the name of Cavium Inc. nor the names of
#     its contributors may be used to endorse or promote products
#     derived from this software without specific prior written
#     permission.
#
# This Software, including technical data, may be subject to U.S. export
# control laws, including the U.S. Export Administration Act and its
# associated regulations, and may be subject to export or import
# regulations in other countries.
#
# TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
# AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
# WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
# TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
# REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
# DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
# OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
# PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
# QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
# ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
# **********************license end**************************************

sub usage
{
print <<END;
 Usage
   $0 [<Options>] <From_Format> <To_Format>  <  <input_file>  >  <output_file>

 Convert: (<From_Format> == trace)

    { 0x0000842000000280, 0x0000000000000000 }, /* TNS_TDMA_SST_ACC_WDAT[0] */
    { 0x0000842000000290, 0xffffffffffffffff }, /* TNS_TDMA_SST_ACC_WDAT[1] */
    { 0x00008420000002a0, 0x0000000000000000 }, /* TNS_TDMA_SST_ACC_WDAT[2] */
    { 0x00008420000002b0, 0xffffffffffffffff }, /* TNS_TDMA_SST_ACC_WDAT[3] */
    { 0x0000842000000270, 0x0000002878e0c440 }, /* TNS_TDMA_SST_ACC_CMD */

 Or: (<From_Format> == cputrans)

  [CPU_TRANS] Target = 5, Write Addr = 1e38311, data = ffffffffffffffff0000000000000000ffffffffffffffff0000000000000000, req_type = 2, word_cnt = 8

 Or: (<From_Format> == hwtrace)

  %I-(+_csr_print_cbs.sv:  45)[global_csr_print_cbs          ]{1003530.136} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_WDAT[0] (addr 0x0000842000000280) being written to value 0x0000000000000000 using ncb_map via UVM_FRONTDOOR
  %I-(+_csr_print_cbs.sv:  56)[global_csr_print_cbs          ]{1003532.636} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_WDAT[0] (addr 0x0000842000000280) write complete with status UVM_IS_OK
  %I-(+_csr_print_cbs.sv:  45)[global_csr_print_cbs          ]{1003532.636} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_WDAT[1] (addr 0x0000842000000290) being written to value 0xffffffffffffffff using ncb_map via UVM_FRONTDOOR
  %I-(+_csr_print_cbs.sv:  56)[global_csr_print_cbs          ]{1003535.136} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_WDAT[1] (addr 0x0000842000000290) write complete with status UVM_IS_OK
  %I-(+_csr_print_cbs.sv:  45)[global_csr_print_cbs          ]{1003535.136} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_WDAT[2] (addr 0x00008420000002a0) being written to value 0x0000000000000000 using ncb_map via UVM_FRONTDOOR
  %I-(+_csr_print_cbs.sv:  56)[global_csr_print_cbs          ]{1003537.636} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_WDAT[2] (addr 0x00008420000002a0) write complete with status UVM_IS_OK
  %I-(+_csr_print_cbs.sv:  45)[global_csr_print_cbs          ]{1003537.636} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_WDAT[3] (addr 0x00008420000002b0) being written to value 0xffffffffffffffff using ncb_map via UVM_FRONTDOOR
  %I-(+_csr_print_cbs.sv:  56)[global_csr_print_cbs          ]{1003540.136} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_WDAT[3] (addr 0x00008420000002b0) write complete with status UVM_IS_OK
  %I-(+_csr_print_cbs.sv:  45)[global_csr_print_cbs          ]{1003540.136} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_CMD (addr 0x0000842000000270) being written to value 0x0000002878e0c440 using ncb_map via UVM_FRONTDOOR
  %I-(+_csr_print_cbs.sv:  56)[global_csr_print_cbs          ]{1003542.636} uvm_reg_access dp_tdma_byp.TNS_TDMA_SST_ACC_CMD (addr 0x0000842000000270) write complete with status UVM_IS_OK

 To: (<To_Format> == cputrans)

   [CPU_TRANS] Target = 5, Write Addr = 1e38311, data = ffffffffffffffff0000000000000000ffffffffffffffff0000000000000000, req_type = 2, word_cnt = 8

 Or: (<To_Format> == trace)

    { 0x00008420000002b0, 0xffffffffffffffff },
    { 0x00008420000002a0, 0x0000000000000000 },
    { 0x0000842000000290, 0xffffffffffffffff },
    { 0x0000842000000280, 0x0000000000000000 },
    { 0x0000842000000270, 0x0000002878e0c440 },

 Or: (<To_Format> == sst-acc)
    0x0000002878e0c440, 0xffffffffffffffff, 0x0000000000000000, 0xffffffffffffffff, 0x0000000000000000, 


 Or: (<To_Format> == playback) (needs more values to see the compression, and creates a header)

    0x0000002878e0c440,         0xffffffffffffffff, 0x0000000000000000, 0xffffffffffffffff, 0x0000000000000000,


 by default, cputrans surpresses leading zeros.  Use -z to not suppress them
 Lines starting with DWRITE or unparsable lines are passed through unchanged.

  <From_Format> or <To_Format>:
    cputrans  [CPU_TRANS] Target = ..., format as above
    trace     trace (address,data pairs) format as above
    sst-acc   array of uint64 data values without address (<To_Format> only for now)
    playback  somewhat compressed sst-acc values (<To_Format> only for now)
    hwtrace   verbose trace format as above (<From_Format> only for now)

  <Options>:
    -h     Show this message
    --help Show this message
    -z     Don't suppress leading zeros in the cputrans format
    -a     Don't suppress repeats (show all)

END
}

$surpress_leading_zeros = 1;
$surpress_repeats = 1;
$last_270 = "";
$last_addr = "";
$format_needed = "From";

$last_value = "";
$last_cmd = "";
$run = 0;
$p2 = 0;
$stride = 0;
$out = "";

sub output_pending_indirect_write
{
   if ($out ne "") {
      $p2 = 0 if ($run == 0);
      printf("    0x%03x", $run | ($p2 << 11));
      print $out;
   }
}

sub output_indirect_write
{
   if ($to_format eq "cputrans") {
      print("[CPU_TRANS] Target = $target, Write Addr = $addr, data = ");
      $leading_nonzero = $surpress_leading_zeros ? 0 : 1;
      while ($size > 0) {
         $acc_addr = "0x00008420000002" . sprintf("%02x",($size+7)*0x10);
         if ($leading_nonzero) {
            $chunk = sprintf("%016x",hex($val{$acc_addr})); # remove 0x
         }
         else {
# still all leading zeros
            if (hex($val{$acc_addr}) != 0) {
               $leading_nonzero = 1;
               $chunk = sprintf("%x",hex($val{$acc_addr})); # remove 0x and leading zeros
            }
            else {
               $chunk = ($size > 1) ? "" : "0";
            }
         }
         print("$chunk");
         $size--;
      }
      print(", req_type = $req_type, word_cnt = $word_cnt\n");
   }
   elsif ($to_format eq "trace") {
      while ($size >= 0) {
         $acc_addr = "0x00008420000002" . sprintf("%02x",($size+7)*0x10);
#         print("    { $acc_addr, $val{$acc_addr} },\n");
         printf("    { $acc_addr, 0x%016x },\n", hex($val{$acc_addr}) );
         $size--;
      }
   }
   elsif ($to_format eq "sst-acc") {
      print("    $val{\"0x0000842000000270\"}, ");
      while ($size > 0) {
         $acc_addr = "0x00008420000002" . sprintf("%02x",($size+7)*0x10);
         print("$val{$acc_addr}, ");
         $size--;
      }
      print("\n");
   }
   elsif ($to_format eq "playback") {
      $cmd = sprintf("$val{\"0x0000842000000270\"}");
      $value = "";
      while ($size > 0) {
         $acc_addr = "0x00008420000002" . sprintf("%02x",($size+7)*0x10);
         $value .= sprintf(" $val{$acc_addr},");
         $size--;
      }
      $delta = (hex($cmd) - hex($last_cmd)) >> 2;
      $last_cmd = $cmd;

      if ($delta != $stride) {
         if (($run == 0) && ($delta == $p2stride)) {
            $p2 = 1;
            $stride = $p2stride;
         }
      }

      if (($last_value ne $value) || ($delta != $stride) || ($run == 0x7ff)) {
         output_pending_indirect_write();

         $c = substr($cmd, 5); # remove "0x000" to make room for run
            $out = sprintf("$c,        $value\n");
         $run = 0;

         ## find two possible strides
         $stride = hex(substr($cmd, 9, 1));
         $stride = 16 if ($stride == 0);
         $p2stride = $stride;
         ## get next power of 2
         while (($p2stride & ($p2stride - 1)) != 0) { $p2stride++; }
         $p2 = 0;
      }
      else {
         $run++;
         $out .= sprintf("//  $cmd, %03x%s$stride%s$value\n", $run,
               $stride == 16 ? "+" : " +", $p2 ? ";" : ",");
      }
      $last_value = $value;
   }
   elsif ($to_format eq "hwtrace") {
      usage();
      die("<To_Format> hwtrace is not supported right now.\n");
   }
   else {
      usage();
      die("ERROR: unknown <To_Format>: '$to_format'\n");
   }
}

sub output_direct_write
{
   printf("DWRITE { $addr, $data },\n");
}

sub parse_cputrans
{
   if ($line =~ /DWRITE.*/) {
      print ($line);
      return;
   }
   if ($line =~ /\[CPU_TRANS\] Target = (\d+)\s*, Write Addr = (\w+)\s*, data = (\w+)\s*, req_type = (\d+)\s*, word_cnt = (\d+)/) {
      $target = $1;
      $addr = $2;
      $data = $3;
      $req_type = $4;
      $word_cnt = $5;

      if ($req_type == 2) { # write
         return if ($surpress_repeats && $addr eq $last_addr);
         $last_addr = $addr;

         $cmd = (hex($addr)<<2);
         $cmd |= $req_type << 36;
         $cmd |= ($word_cnt==16) ? 0 : $word_cnt << 32;
         $cmd |= $target << 28;

         # pad to size with leading zeros to make it easier below.  Note, not efficient!
         while (length($data) < $word_cnt * 32) {
             $data = "0" . $data;
         }

         $size = int(($word_cnt + 1) / 2); # in 64-bit words
         $offset = 0;
         while ($offset < $size) {
            $acc_addr = "0x00008420000002" . sprintf("%02x",($offset+8)*0x10);
            # use as string since too long for perl math.  Note zero padded above
            $val{$acc_addr} = substr($data, -16);
            $data = substr($data, 0, (length($data) - 16));
            $offset++;
         }
         $val{"0x0000842000000270"} = sprintf("0x%016x", $cmd);

         $size = int(($word_cnt + 1) / 2); # in 64-bit words

         output_indirect_write();
      }
   }
   else {
      print $line;
   }
}

sub parse_trace
{
   if ($line =~ /DWRITE.*/) {
      print ($line);
      return;
   }
   if ($line =~ /.*\{ (0x\w*), (0x\w*) \}.*/) {
      $val{$1} = $2;
      if ($1 eq "0x0000842000000270") {
         return if ($surpress_repeats && $2 eq $last_270);
         $last_270 = $2;
         $word_cnt = (hex($2)>>32) & 0xF;
         $word_cnt = ($word_cnt==0) ? 16 : $word_cnt;
         $size = int(($word_cnt + 1) / 2); # in 64-bit words
         $addr = sprintf("%x", (hex($2)>>2) & 0x3ffffff);
         $go_op = (hex($2)>>36) & 0x3;
         $req_type = $go_op;
         $target = (hex($2)>>28) & 0x7;

         output_indirect_write();
      }
   }
   else {
      print $line;
   }
}

sub parse_sst_acc
{
    print("<From_Format> == 'sst-acc' is not implemented yet.\n");
}

sub parse_playback
{
    print("<From_Format> == 'playback' is not implemented yet.\n");
}

sub parse_hwtrace
{
# note, in this format, we drop most lines
   if ($line =~ /.*\(addr (0x\w*)\) being written to value (0x\w*) using.*/) {
      $val{$1} = $2;
      if ($1 eq "0x0000842000000270") {
         return if ($surpress_repeats && $2 eq $last_270);
         $last_270 = $2;
         $word_cnt = (hex($2)>>32) & 0xF;
         $word_cnt = ($word_cnt==0) ? 16 : $word_cnt;
         $size = int(($word_cnt + 1) / 2); # in 64-bit words
         $addr = sprintf("%x", (hex($2)>>2) & 0x3ffffff);
         $go_op = (hex($2)>>36) & 0x3;
         $req_type = $go_op;
         $target = (hex($2)>>28) & 0x7;

         output_indirect_write();
      }
      elsif ((hex($1) < 0x0000842000000270) || (hex($1) > 0x00008420000002f0)) {
         $addr = $1;
         $data = $2;
         output_direct_write();
      }
   }
}

$compat_ver = '1.7';  # Now that we are in svn, update manually if the format
                      #   changes in a way that software needs to know about.
                      # This gets written to the header in playback mode.
print("// Converted by '$0 @ARGV' compat_ver: $compat_ver.\n");

while ($#ARGV >= 0) {
  if ($ARGV[0] eq "-z") {
    $surpress_leading_zeros = 0;
    shift;
  }
  elsif ($ARGV[0] eq "-a") {
    $surpress_repeats = 0;
    shift;
  }
  elsif (($ARGV[0] eq "-h") or ($ARGV[0] eq "--help")) {
    usage();
    exit(0);
  }
  else {
    if ($format_needed eq "From") {
       $from_format = $ARGV[0];
       $format_needed = "To";
    }
    elsif ($format_needed eq "To") {
       $to_format = $ARGV[0];
       $format_needed = "none";
    }
    else {
       usage();
       die("ERROR: Unknown option or format: '$ARGV[0]'");
    }
    shift();
  }
}

if ($format_needed ne "none") {
    usage();
    die("ERROR: missing <$format_needed\_Format>");
}

if ($to_format eq "playback") { # create header with magic number and BCD major and minor versions
   $compat_ver =~ /(\d+)\.(\d+)/;
   printf("0x0000abac0000%02d%02d,   // playback v%d.%d header\n", $1, $2, $1, $2);
}

foreach $line (<STDIN>) {
   if ($from_format eq "trace") {
      parse_trace();
   }
   elsif ($from_format eq "cputrans") {
      parse_cputrans();
   }
   elsif ($from_format eq "sst-acc") {
      parse_sst_acc();
   }
   elsif ($from_format eq "playback") {
      parse_playback();
   }
   elsif ($from_format eq "hwtrace") {
      parse_hwtrace();
   }
   else {
      usage();
      die("ERROR: unknown <From_Format>: '$from_format'\n");
   }
}

output_pending_indirect_write();

