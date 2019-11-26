domain domain0 @(posedge Uclock);
state S0 : initial
begin
 next ( ( tb.fc_wrapper.fc.roc.cpc.cpc.scp_core.core.core.cpz._epc_m_31_0_.d[31:20] = 12'h800 ));
end
state S1 : trigger, stop;











