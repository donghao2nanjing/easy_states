#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd 
import os 
import math 


# In[2]:


csv_config_path = "../example/state.csv"
template_path = "state_init_gen.c.template"
output_cfile_path = "../example/state_init.c"

df = pd.read_csv(csv_config_path, sep=',', header=0)

df.info() 
df


# In[3]:


'''
period: state check period in ms 
valid_time_or_cnt: time in ms that state is set valid 
recover_time_or_cnt: time in ms that state is reset 
'''
def compute_counter_and_step(period:int, valid_time_or_cnt:int, recover_time_or_cnt:int):
    if valid_time_or_cnt < period :
        valid_time_or_cnt = period
        print("Warning")
    if recover_time_or_cnt < period:
        recover_time_or_cnt = period
        print("Warning")
    
    valid_ticks = int(valid_time_or_cnt/period) 
    recover_ticks = int(recover_time_or_cnt/period)
    
    gcd = math.gcd(valid_ticks, recover_ticks)
    lcm = valid_ticks * recover_ticks / gcd
    
    valid_step = lcm / valid_ticks
    recover_step = lcm / recover_ticks
    
    return lcm, valid_step, recover_step 
    
# Test this function:
# compute_counter_and_step(100, 400, 300)
# compute_counter_and_step(100, 10000, 300)


# In[4]:


states_gen_list = [] 

for idx, row in df.iterrows(): 
    if row['state'].replace(' ', '').replace('\r', '').replace('\n', '') == '': 
        continue # ignore this row 
    state_init_gen_list = [] 

    state_init_gen_list.append('\t/* '  + row['comment'] + ' */\n')
        
    for k in row.keys(): 
        if k in ['state', 'comment', 'period', 'valid_time_or_cnt', 'recover_time_or_cnt']: 
            continue; 
            
        state_init_gen_list.append( ("\t{}." + k + " = {};\n").format(row['state'], row[k]) )
        
    if row['valid_threshold'] > row['recover_threshold']:
        state_trig_type = 'OVER_THRESHOLD_VALID'
    else:
        state_trig_type = 'UNDER_THRESHOLD_VALID'
        
    state_init_gen_list.append("\t{}.status.bits.type = {};\n".format(row['state'], state_trig_type))
    
    if row['status.bits.check_by'] == 'PERIOD_CHECK':
        cnt_max, valid_step, recover_step = compute_counter_and_step(row['period'], 
                                                                     row['valid_time_or_cnt'],
                                                                     row['recover_time_or_cnt'])
    elif row['status.bits.check_by'] == 'COUNT_CHECK': 
        cnt_max, valid_step, recover_step = compute_counter_and_step(1, 
                                                             row['valid_time_or_cnt'],
                                                             row['recover_time_or_cnt'])
    else:
        print('Warning: Undefined check typoe.')
        state_init_gen_list.append("\t{}._cnt_max = {};\n".format(row['state'], 0))
        state_init_gen_list.append("\t{}._step_valid = {};\n".format(row['state'], 0))
        state_init_gen_list.append("\t{}._step_recover = {};\n".format(row['state'], 0))
        continue 
    
    state_init_gen_list.append("\t{}._cnt_max = {};\n".format(row['state'], cnt_max))
    state_init_gen_list.append("\t{}._step_valid = {};\n".format(row['state'], valid_step))
    state_init_gen_list.append("\t{}._step_recover = {};\n".format(row['state'], recover_step))
    
    state_init_gen_list.append('\n')
    
    states_gen_list += state_init_gen_list 


# In[5]:


states_declaration_list = [] 
for idx, row in df.iterrows():
    states_declaration_list.append("state {} ;\n".format(row['state']))


# In[6]:


f_template = open(template_path, 'r')
existed_lines = f_template.readlines()

def generate_from_template(list_template_lines, inserted_lines, position_line):
    index = -1 
    for idx, line in enumerate(list_template_lines):
        # find the position to insert code 
        if position_line in line:
            index = idx 
    
    if index == -1 :
        return list_template_lines # do not insert anything 
    
    return list_template_lines[:index+1] + inserted_lines + list_template_lines[index+1:]



existed_lines = generate_from_template(existed_lines, states_gen_list, 'generated code for state initialization')
existed_lines = generate_from_template(existed_lines, states_declaration_list, 'decalaration of states')

for line in existed_lines: 
    print(line)


# In[7]:


with open(output_cfile_path, 'w') as f : 
    f.writelines(existed_lines)


# In[ ]:




