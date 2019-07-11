#pragma once
#include <memory>

template <class T, class Alloc = std::allocator<T>>
class fwd_list
{
public:
    using value_type = T;
    using allocator_type = Alloc;
    using alloc_traits = std::allocator_traits<allocator_type>;
    using pointer = typename alloc_traits::pointer;
    using const_pointer = typename alloc_traits::const_pointer;
    using size_type = typename alloc_traits::size_type;
    using difference_type = typename alloc_traits::difference_type;
    using reference = value_type &;
    using const_reference = const value_type &;
private:
	struct node_type
    {
		T value_;
        node_type *next_;
		node_type():value{T()}, next_{nullptr}{}
		node_type(const node_type & rhs):value_(rhs.value), next_(rhs.next_),{}
	};

	node_type head_;
	node_type *tail_ = nullptr;
    allocator_type allocator_;
public:
    fwd_list():head_, tail_(&head){};
    void push_back(const T& value)
    {
        tail->
    }

    class fwd_list_iter
    {
        private:
            node *node_;
        public:
            fwd_list_iter():node_(nullptr){}
            fwd_list_iter(const fwd_list_iter& rhs):node_(rhs.node_){}
            ~fwd_list_iter() = default;

            T& operator*()
            {
                if(node == nullptr) throw()
            }
    };

	int size(){
		return _size;
	}
	void append(T & element){
			
		unique_ptr<Node,Deleter> new_node(_allocator.allocate(1),Deleter());

		new_node->nxt=unique_ptr<Node,Deleter>(head.release());	
		new_node->value=element;
		head = std::move(new_node);
		++_size;
	}
	void print(ostream * stream,string delim=" "){
		for (auto curr=head.get(); curr; curr=curr->nxt.get())
			(*stream)<<curr->value<<delim;
	}
};