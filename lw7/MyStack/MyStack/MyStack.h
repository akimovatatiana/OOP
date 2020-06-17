#pragma once
#include "stdafx.h"

const std::string POP_FAILED = "Failed to pop from empty stack.";
const std::string GET_TOP_FAILED = "Failed to get top element from empty stack.";

template <typename T>
class CMyStack
{
public:
	CMyStack() = default;

	void Clear()
	{
		while (!IsStackEmpty())
		{
			Pop();
		}
	}

	bool IsStackEmpty() const
	{
		return m_size == 0;
	}

	~CMyStack()
	{
		Clear();
	}

	void Push(T const& value)
	{
		auto newNode = std::make_shared<Node>(value, m_pTop);
		m_pTop = newNode;
		m_size++;
	}

	void Pop()
	{
		if (IsStackEmpty())
		{
			throw std::logic_error(POP_FAILED);
		}
		m_pTop = m_pTop->next;
		m_size--;
	}

	T GetTopElement() const
	{
		if (IsStackEmpty())
		{
			throw std::logic_error(GET_TOP_FAILED);
		}
		return m_pTop->value;
	}

	size_t GetSize() const
	{
		return m_size;
	}

	CMyStack(CMyStack<T> const& stack)
	{
		if (!stack.IsStackEmpty())
		{
			*this = stack;
		}
	}

	CMyStack<T>& operator=(CMyStack<T> const& stack)
	{
		if (this != std::addressof(stack))
		{
			Clear();
			if (!stack.IsStackEmpty())
			{
				m_size = stack.m_size;
				std::shared_ptr<Node> copiedNode = stack.m_pTop;

				m_pTop = std::make_shared<Node>(*copiedNode);
				auto node = m_pTop;

				while (copiedNode->next != nullptr)
				{
					node->next = std::make_shared<Node>(*copiedNode->next);

					copiedNode = copiedNode->next;
					node = node->next;
				}
			}
		}
		return *this;
	}

	CMyStack(CMyStack<T>&& stack)
	{
		if (!stack.IsStackEmpty())
		{
			*this = std::move(stack);
		}
	}

	CMyStack<T>& operator=(CMyStack<T>&& stack)
	{
		if (this != std::addressof(stack))
		{
			m_pTop = stack.m_pTop;
			m_size = stack.m_size;
			stack.m_pTop = nullptr;
			stack.m_size = 0;
		}
		return *this;
	}
private:
	struct Node
	{
		Node(T const& value, std::shared_ptr<Node> const& next)
			: value(value)
			, next(next)
		{
		}
		T value;
		std::shared_ptr<Node> next = nullptr;
	};

	size_t m_size = 0;
	std::shared_ptr<Node> m_pTop = nullptr;
};