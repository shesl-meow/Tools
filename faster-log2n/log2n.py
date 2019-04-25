mask_list = []
count = [1, 2]

def init_mask():
	mask_list.append(0x2)
	for i in range(1, 12):
		count.append(count[i] * count[i])
		this_mask = \
			mask_list[i-1] << count[i] + \
			mask_list[i-1] << (count[i-1])
		mask_list.append(this_mask)
init_mask()

def max_bit(num):
	r = 0
	for i in range(0, 12)[::-1]:
		if num & mask_list[i]:
			v >>= count[i]
			r |= count[i]
	return r;
